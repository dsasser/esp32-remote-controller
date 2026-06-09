/**
 * Remote Controller Firmware
 * ESP32-S3 Super Mini — 4-Channel BLE Remote
 *
 * BLE GATT Service with single writable characteristic.
 * Write "1"–"4" to fire channels, "A" for all, "S" for status.
 *
 * License: MIT
 * Repository: https://github.com/[your-username]/remote-controller
 */

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

// ─── Configuration ───────────────────────────────────────────────
#define CH1_PIN   4       // GPIO for relay channel 1
#define CH2_PIN   5       // GPIO for relay channel 2
#define CH3_PIN   6       // GPIO for relay channel 3
#define CH4_PIN   7       // GPIO for relay channel 4
#define LED_PIN   2       // GPIO for status LED

#define FIRE_MS   1000    // Pulse duration in milliseconds

#define BLE_NAME  "RemoteBox"   // Appears in BLE scan list

// Most prebuilt relay modules are active-LOW (LOW = relay ON)
// Set to false if your module fires on HIGH
#define RELAY_ACTIVE_LOW  true

// BLE UUIDs — generate your own at uuidgenerator.net if forking
#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"
// ─────────────────────────────────────────────────────────────────

// Relay ON/OFF helpers that respect RELAY_ACTIVE_LOW
#define RELAY_ON  (RELAY_ACTIVE_LOW ? LOW  : HIGH)
#define RELAY_OFF (RELAY_ACTIVE_LOW ? HIGH : LOW)

const int CH_PINS[] = { CH1_PIN, CH2_PIN, CH3_PIN, CH4_PIN };
const int NUM_CHANNELS = 4;

BLEServer*         pServer         = nullptr;
BLECharacteristic* pCharacteristic = nullptr;
bool               deviceConnected = false;

// ─── Channel firing ───────────────────────────────────────────────

void fireChannel(int pin) {
  // Blink LED during firing
  digitalWrite(LED_PIN, LOW);
  digitalWrite(pin, RELAY_ON);
  delay(FIRE_MS);
  digitalWrite(pin, RELAY_OFF);
  // Restore LED to connected state
  digitalWrite(LED_PIN, deviceConnected ? HIGH : LOW);
}

void fireAll() {
  digitalWrite(LED_PIN, LOW);
  for (int i = 0; i < NUM_CHANNELS; i++) {
    digitalWrite(CH_PINS[i], RELAY_ON);
  }
  delay(FIRE_MS);
  for (int i = 0; i < NUM_CHANNELS; i++) {
    digitalWrite(CH_PINS[i], RELAY_OFF);
  }
  digitalWrite(LED_PIN, deviceConnected ? HIGH : LOW);
}

// ─── BLE callbacks ────────────────────────────────────────────────

class ServerCallbacks : public BLEServerCallbacks {
  void onConnect(BLEServer* pSvr) override {
    deviceConnected = true;
    digitalWrite(LED_PIN, HIGH);   // Solid = connected
    Serial.println("BLE client connected");
  }

  void onDisconnect(BLEServer* pSvr) override {
    deviceConnected = false;
    digitalWrite(LED_PIN, LOW);
    Serial.println("BLE client disconnected — restarting advertising");
    // Restart advertising so another device can connect
    BLEDevice::startAdvertising();
    blinkLED(3, 200);              // 3 blinks = advertising
  }
};

class CharCallbacks : public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic* pChar) override {
    String val = String(pChar->getValue().c_str());
    val.trim();
    Serial.print("Received command: ");
    Serial.println(val);

    if      (val == "1") fireChannel(CH1_PIN);
    else if (val == "2") fireChannel(CH2_PIN);
    else if (val == "3") fireChannel(CH3_PIN);
    else if (val == "4") fireChannel(CH4_PIN);
    else if (val == "A" || val == "a") fireAll();
    else if (val == "S" || val == "s") {
      // Status response — set characteristic value to "OK"
      pChar->setValue("OK");
      pChar->notify();
    }
    else {
      Serial.println("Unknown command — valid: 1 2 3 4 A S");
    }
  }
};

// ─── Helpers ──────────────────────────────────────────────────────

void blinkLED(int count, int ms) {
  for (int i = 0; i < count; i++) {
    digitalWrite(LED_PIN, HIGH);
    delay(ms);
    digitalWrite(LED_PIN, LOW);
    delay(ms);
  }
}

// ─── Setup ────────────────────────────────────────────────────────

void setup() {
  Serial.begin(115200);
  Serial.println("\nRemote Controller booting...");

  // Configure output pins
  for (int i = 0; i < NUM_CHANNELS; i++) {
    pinMode(CH_PINS[i], OUTPUT);
    digitalWrite(CH_PINS[i], RELAY_OFF);  // All relays OFF at boot
  }
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  // BLE setup
  BLEDevice::init(BLE_NAME);

  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new ServerCallbacks());

  BLEService* pService = pServer->createService(SERVICE_UUID);

  pCharacteristic = pService->createCharacteristic(
    CHARACTERISTIC_UUID,
    BLECharacteristic::PROPERTY_WRITE |
    BLECharacteristic::PROPERTY_NOTIFY
  );
  pCharacteristic->addDescriptor(new BLE2902());
  pCharacteristic->setCallbacks(new CharCallbacks());

  pService->start();

  BLEAdvertising* pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);
  BLEDevice::startAdvertising();

  Serial.println("BLE advertising as: " BLE_NAME);
  Serial.println("Service UUID: " SERVICE_UUID);
  Serial.println("Ready.");

  // 3 blinks = advertising and ready
  blinkLED(3, 200);
}

// ─── Loop ─────────────────────────────────────────────────────────

void loop() {
  // All work is done in BLE callbacks.
  // Keep loop empty or add watchdog logic here if needed.
  delay(100);
}

// ─── WiFi Alternative (commented out) ────────────────────────────
//
// Uncomment this block and comment out the BLE setup above to use
// WiFi with a simple web server instead. The ESP32-S3 hosts its own
// access point — no router needed.
//
// #include <WiFi.h>
// #include <WebServer.h>
//
// const char* AP_SSID = "RemoteBox";
// const char* AP_PASS = "12345678";   // min 8 chars for WPA2
// WebServer server(80);
//
// void handleRoot() {
//   server.send(200, "text/html",
//     "<h2>Remote Controller</h2>"
//     "<button onclick=\"fetch('/fire?ch=1')\">CH1</button>"
//     "<button onclick=\"fetch('/fire?ch=2')\">CH2</button>"
//     "<button onclick=\"fetch('/fire?ch=3')\">CH3</button>"
//     "<button onclick=\"fetch('/fire?ch=4')\">CH4</button>"
//   );
// }
//
// void handleFire() {
//   int ch = server.arg("ch").toInt();
//   if (ch >= 1 && ch <= 4) {
//     fireChannel(CH_PINS[ch - 1]);
//     server.send(200, "text/plain", "OK");
//   } else {
//     server.send(400, "text/plain", "Invalid channel");
//   }
// }
//
// // In setup():
// // WiFi.softAP(AP_SSID, AP_PASS);
// // server.on("/", handleRoot);
// // server.on("/fire", handleFire);
// // server.begin();
//
// // In loop():
// // server.handleClient();
