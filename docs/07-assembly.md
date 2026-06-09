# 07 — Assembly Guide

Follow this order. Each stage can be tested before moving to the next — don't skip ahead.

---

## Stage 1 — Logic Power Chain

**Goal:** Get stable 5V from the 18650 cell before anything else is connected.

1. Solder wire leads to the 18650 holder if not pre-attached (red = positive, black = negative)
2. Insert the 18650 cell into the holder
3. Wire holder B+ → TP4056 B+, holder B− → TP4056 B−
4. If the cell is fresh from storage, plug USB-C into the TP4056 first — this activates the protection circuit. Wait for the charge indicator LED to respond.
5. Wire TP4056 OUT+ → MT3608 IN+, TP4056 OUT− → MT3608 IN−
6. Power the MT3608. Measure the output with a multimeter.
7. **Adjust the MT3608 trimmer pot until output reads 5.00V ± 0.05V.** Turn slowly — the pot is sensitive.
8. Note which direction increases/decreases voltage for future reference.

✅ **Test:** Multimeter reads 5.00V on MT3608 output. No components connected downstream yet.

---

## Stage 2 — ESP32-S3 First Boot

**Goal:** Confirm the ESP32-S3 boots and can be programmed.

1. Solder female 2.54mm headers to the ESP32-S3 footprint on your ElectroCookie board
2. Plug the ESP32-S3 Super Mini into the headers
3. Connect MT3608 OUT+ to the board's 5V rail, MT3608 OUT− to GND rail
4. Open Arduino IDE, select ESP32S3 Dev Module, plug in via USB-C
5. Flash the basic blink sketch (File → Examples → Basics → Blink) to confirm the toolchain works
6. Flash the main firmware from `/firmware/remote_controller/`
7. Open Serial Monitor at 115200 baud — you should see startup messages and `BLE advertising as RemoteBox`

✅ **Test:** nRF Connect on your phone finds `RemoteBox` in the BLE scan list.

---

## Stage 3 — Relay Module Logic Test

**Goal:** Confirm all four relay channels fire correctly from BLE commands before connecting 12V.

1. Solder female headers to the relay module footprint on the board
2. Plug the relay module in
3. Ensure relay module JD-VCC jumper is **removed** — if it's still on, remove it now
4. Wire:
   - Relay VCC → 5V bus
   - Relay GND → GND bus
   - Relay IN1 → ESP32 GPIO4
   - Relay IN2 → ESP32 GPIO5
   - Relay IN3 → ESP32 GPIO6
   - Relay IN4 → ESP32 GPIO7
5. **Do not connect JD-VCC or 12V yet**
6. Power the logic chain (18650 → TP4056 → MT3608 → ESP32)
7. Open nRF Connect, connect to `RemoteBox`, write `"1"` then `"2"` then `"3"` then `"4"`

✅ **Test:** Each relay clicks audibly when the corresponding command is sent. The relay module LED lights. The LED on the ESP32 blinks during firing.

---

## Stage 4 — 12V Switching Power

**Goal:** Add the 12V domain and confirm it doesn't interfere with the logic side.

1. Wire the inline fuse holder in series with the LiFePO4 BAT+ lead. Install a **5A fuse**.
2. Wire fuse output → master switch SW1 input terminal
3. Wire SW1 output terminal → 12V bus on the PCB
4. Wire LiFePO4 BAT− → GND bus on the PCB
5. Wire relay K1 JD-VCC pin → 12V bus (short direct wire, not through SW1)
6. Wire relay K1 COM1, COM2, COM3, COM4 → 12V bus (all four in parallel to the bus)
7. Turn on SW1. Measure 12V bus voltage with multimeter — should read ~12.8V.
8. Measure 5V bus — should be unchanged at 5.00V.

✅ **Test:** Both voltage rails present simultaneously. No interference.

---

## Stage 5 — Output Channels

**Goal:** Wire and test all four output channels.

For each channel (repeat ×4):

1. Solder a TVS diode (D2–D5) — **cathode stripe to + post, anode to − post**
2. Wire relay NO terminal → binding post red (+)
3. Wire GND bus → binding post black (−)
4. Mount binding posts in the front panel holes

With 12V on and a relay firing, measure voltage across the binding posts with a multimeter. Should read ~12.8V when fired, 0V when idle.

✅ **Test:** All four channels show 12V at the binding posts when fired via BLE.

---

## Stage 6 — Decoupling Capacitors and LED

1. Solder C1 (100µF) between 5V bus and GND, as close to ESP32 VIN as possible
2. Solder C2–C5 (0.1µF) each between relay IN1–IN4 signal lines and GND
3. Wire R1 (330Ω) in series from ESP32 GPIO2 to D1 LED anode
4. Wire D1 LED cathode to GND

✅ **Test:** Status LED is solid when BLE connected, blinks during firing.

---

## Stage 7 — Enclosure

1. Drill front and rear panels per the hole chart in [05-enclosure.md](05-enclosure.md) or use the DXF template
2. Deburr all holes
3. Mount binding posts in front panel — red to + holes, black to − holes
4. Mount status LED in 5mm hole — use a rubber grommet or hot glue to secure
5. Mount master switch SW1 in rear panel slot
6. Mount 12V barrel jack J1 in rear 12mm hole
7. Mount USB-C panel jack J2 in rear slot
8. Extend all panel-mounted component wires with enough slack (~80mm) to allow panels to swing open for servicing
9. Install the PCB on standoffs inside the enclosure
10. Secure LiFePO4 battery with hook-and-loop or foam tape
11. Secure 18650 holder
12. Route and dress all wiring — keep 12V and 5V wire bundles separate where possible
13. Slide enclosure body over assembly, close end panels

✅ **Final test:**
- Master switch ON → 12V bus live
- BLE connects from phone
- All 4 channels fire via nRF Connect
- Status LED behaves correctly
- No abnormal heat after 5 minutes of use

---

## Servicing Notes

- All modules are socket-mounted and can be replaced without soldering
- Fuse F1 is accessible from the rear panel wiring — no need to open enclosure
- To replace the 18650 cell: open the enclosure, disconnect the holder leads, swap cell
- To replace the LiFePO4 battery: open enclosure, disconnect BAT+/BAT−, swap battery
- End panels are held by four Phillips screws — a magnetic screwdriver helps in the tight space

---

## Safety Checklist

Before using with real devices:

- [ ] Fuse installed and correct rating (5A)
- [ ] JD-VCC jumper removed from relay module
- [ ] MT3608 output verified at 5.00V
- [ ] TVS diodes installed with correct orientation (cathode to + post)
- [ ] All connections secure — tug test each terminal
- [ ] No exposed conductors that could short against the aluminum enclosure
- [ ] Master switch confirms 12V rail is disconnectable
- [ ] Devices rated for 12V and tested at low duty before full use
