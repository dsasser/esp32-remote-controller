# 06 — Firmware

## Overview

The firmware runs on the ESP32-S3 Super Mini using the Arduino ESP32 core. It exposes a BLE GATT service with a single writable characteristic. Writing the values `"1"` through `"4"` fires the corresponding channel for the configured pulse duration.

The complete firmware source is in `/firmware/remote_controller/remote_controller.ino`.

---

## Development Environment Setup

### 1. Install Arduino IDE

Download from [arduino.cc/en/software](https://www.arduino.cc/en/software). Version 2.x recommended.

### 2. Add ESP32 Board Support

In Arduino IDE: **File → Preferences → Additional boards manager URLs**, add:

```
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
```

Then: **Tools → Board → Boards Manager**, search `esp32`, install **esp32 by Espressif Systems** (version 3.x recommended).

### 3. Select Board

**Tools → Board → ESP32 Arduino → ESP32S3 Dev Module**

Settings:
- USB Mode: **USB-OTG (TinyUSB)**
- Upload Mode: **UART0 / Hardware CDC**
- Flash Size: **4MB**
- Partition Scheme: **Default 4MB with spiffs**

### 4. Select Port

Plug the ESP32-S3 Super Mini in via USB-C. If no port appears, hold the BOOT button while plugging in. Select the corresponding port under **Tools → Port**.

---

## Flashing

With the board selected and port set, open `/firmware/remote_controller/remote_controller.ino` and click **Upload** (→ arrow). The IDE compiles and flashes. The status LED will blink 3 times then hold solid when BLE is advertising.

If the upload fails: hold BOOT on the ESP32-S3, press and release RESET, then release BOOT. This forces download mode.

---

## BLE Protocol

| Property | Value |
|----------|-------|
| Device name | `RemoteBox` |
| Service UUID | `4fafc201-1fb5-459e-8fcc-c5c9c331914b` |
| Characteristic UUID | `beb5483e-36e1-4688-b7f5-ea07361b26a8` |
| Characteristic property | WRITE |

### Commands

Write a single ASCII character to the characteristic:

| Value | Action |
|-------|--------|
| `"1"` | Fire channel 1 |
| `"2"` | Fire channel 2 |
| `"3"` | Fire channel 3 |
| `"4"` | Fire channel 4 |
| `"A"` | Fire all channels simultaneously |
| `"S"` | Status query (returns `"OK"` if connected) |

### Testing Without an App

Use **nRF Connect** (iOS / Android — free):

1. Open nRF Connect, tap **SCAN**
2. Find `RemoteBox` in the list, tap **CONNECT**
3. Navigate to the service UUID, expand the characteristic
4. Tap the **↑ Upload** icon to write
5. Type `1`, `2`, `3`, or `4`, tap **SEND**
6. You should hear the relay click

---

## LED Status Codes

| Pattern | Meaning |
|---------|---------|
| 3 blinks, then solid ON | BLE advertising, ready |
| Solid ON | BLE connected |
| OFF | Not powered / error |
| Fast blink (100ms) | Firing in progress |

---

## Configuration

At the top of `remote_controller.ino`, adjust these defines to customize behavior:

```cpp
// GPIO assignments — match your wiring
#define CH1_PIN   4
#define CH2_PIN   5
#define CH3_PIN   6
#define CH4_PIN   7
#define LED_PIN   2

// Pulse duration in milliseconds
#define FIRE_MS   1000

// BLE device name (appears in phone scan list)
#define BLE_NAME  "RemoteBox"

// Active LOW relay logic (true for most prebuilt relay modules)
// Set to false if your relay fires on HIGH
#define RELAY_ACTIVE_LOW  true
```

---

## WiFi Alternative

If you prefer WiFi control over BLE, a web server approach is straightforward with the ESP32 Arduino core. The ESP32-S3 can host its own access point — no router needed. See the commented-out WiFi section at the bottom of the firmware file for a starting point.

WiFi adds ~1–2 seconds of connection time vs BLE's near-instant connection, but gives you a browser-based UI on any device.

---

## ESP-NOW Option (future)

For a dedicated physical button controller (a second ESP32-S3 as a handset), ESP-NOW provides:

- No pairing or handshake — just power on and it works
- Sub-10ms latency
- ~200m range
- Works without any phone

See the `firmware/esp_now_controller/` directory (planned — contributions welcome).

---

## Troubleshooting

| Problem | Likely cause | Fix |
|---------|-------------|-----|
| Relay clicks but device doesn't activate | 12V battery off or fuse blown | Check SW1 and F1 |
| BLE not appearing in scan | Wrong board selected, or crash at boot | Check serial monitor at 115200 baud |
| All relays fire on boot | Relay active-HIGH logic mismatch | Set `RELAY_ACTIVE_LOW false` |
| Upload fails | ESP32-S3 not in download mode | Hold BOOT, tap RESET, release BOOT |
| LED stays off | Wrong LED pin or LED polarity | Check GPIO2 and LED orientation |
| MT3608 output too high | Pot not pre-adjusted | Adjust to 5.00V before connecting |
