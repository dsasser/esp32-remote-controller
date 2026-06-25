# 07 — Assembly Guide

Build in stages. Test each before moving on.

---

## Stage 1 — Battery Pack & BMS

1. Assemble the 2S pack: 2x Samsung 30Q in series in the holder (or series-wire two single holders)
2. Wire the pack to the 2S BMS: B+ / B- and the mid-point tap per the BMS markings
3. The BMS P+ / P- are the protected output (7.4V)
4. Verify pack voltage at P+ / P- with a multimeter — should read ~7.4-8.4V depending on charge

**Test:** ~7.4V present at BMS output, no heat, no spark on connection.

---

## Stage 2 — Charging Check

1. Wire the DaierTek barrel jack to the BMS charge input
2. Plug in the 8.4V charger
3. Confirm the pack charges (BMS LED or rising voltage toward 8.4V)

**Test:** Pack charges to 8.4V and the charger tapers off.

---

## Stage 3 — MT3608 to 5.0V

1. Wire BMS output (7.4V) to MT3608 IN+ / IN-
2. Power the MT3608, measure OUT+ / OUT-
3. **Adjust the trimmer pot until output reads 5.00V ± 0.05V.** Turn slowly.

**Test:** Stable 5.00V at MT3608 output. Nothing downstream connected yet.

---

## Stage 4 — ESP32-S3 First Boot

1. Solder female headers to the ElectroCookie center zone; plug in the ESP32-S3
2. Wire MT3608 5V -> board 5V rail, GND -> GND rail
3. Flash a blink sketch over USB-C to confirm the toolchain
4. Flash the main firmware from `/firmware/remote_controller/`
5. Confirm `RemoteBox` appears in a BLE scan (nRF Connect)

**Test:** Phone sees `RemoteBox` over BLE.

---

## Stage 5 — Relay (off-board) Logic Test

1. Bolt the VNFOCKQSH relay to the enclosure floor (M3)
2. Confirm the JD-VCC jumper is removed and the H/L trigger jumper matches firmware (default active-LOW)
3. Run the 6-wire ribbon: GND, 5V, IN1->GPIO4, IN2->GPIO5, IN3->GPIO6, IN4->GPIO7
4. Power logic only (no 7.4V to COM yet)
5. From nRF Connect, write "1"-"4"

**Test:** Each relay clicks on the matching command; relay LEDs light.

---

## Stage 6 — Firing Power

1. Wire the 5A blade fuse holder in series with BMS 7.4V output
2. Fused 7.4V -> relay COM x4 (parallel to the bus)
3. Measure: 7.4V at COM, 5V rail unchanged

**Test:** Both rails present, no interference.

---

## Stage 7 — Output Channels

For each channel:
1. TVS diode (D2-D5) across the output — cathode stripe to + post
2. Relay NO -> binding post + (red)
3. GND -> binding post - (black)

**Test:** With a relay fired, ~7.4V across the binding posts; 0V idle.

---

## Stage 8 — LED, Caps, Enclosure

1. C1 (100µF) across the 5V rail near the ESP32
2. C2-C5 (0.1µF) at each relay IN line
3. R1 + D1 LED on GPIO2 out to the front panel (15cm lead)
4. Mount binding posts, LED, USB-C receptacle, barrel jack to panels
5. Secure PCB, relay, 2S pack, and the inline fuse holder inside
6. Dress wiring, close panels

**Final test:**
- BLE connects
- All 4 channels fire and show 7.4V at the posts
- LED solid when connected, blinks on fire
- No abnormal heat after a few minutes

---

## Safety Checklist (igniters)

- [ ] 5A fuse installed
- [ ] JD-VCC jumper removed; H/L trigger matches firmware
- [ ] MT3608 verified at 5.00V
- [ ] TVS cathode to + post on every channel
- [ ] Relays confirmed open (safe) at power-up
- [ ] All terminals tug-tested
- [ ] No bare conductors near the aluminum enclosure
- [ ] Igniters connected last, system kept unpowered until ready to fire
- [ ] Safe distance per NAR/Tripoli guidelines
