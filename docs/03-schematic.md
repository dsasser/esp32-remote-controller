# 03 — Schematic

## Overview

The circuit splits into two isolated power domains. The schematic is presented as a wiring diagram rather than a traditional EDA schematic — all components are modules, so the focus is on correct interconnection rather than component-level detail.

---

## Power Domains

```
LOGIC DOMAIN (5V)                    SWITCHING DOMAIN (12V)
─────────────────                    ──────────────────────
[18650 Cell B2]                      [LiFePO4 B1]
    │                                    │
[TP4056 U3] ◄── USB-C (J2)          [SW1 Master Switch]
    │                                    │
[MT3608 U4] → 5.0V bus               [F1 5A Fuse]
    │                                    │
[ESP32-S3 U2]                        12V BUS ──────────────────────┐
[Relay VCC/GND]                          │                          │
[Status LED D1+R1]               [Relay COM×4] ◄── tied to 12V   │
                                         │                          │
                              [Relay NO×4]                     [JD-VCC]
                                         │
                              [TVS D2–D5]
                                         │
                              [Binding Posts BT1–BT4]
                                         │
                                    [Devices]

GND: shared common reference between both domains
```

---

## Designators

| Ref | Component |
|-----|-----------|
| B1 | 12.8V 6Ah LiFePO4 battery (switching power) |
| B2 | 18650 ~3000mAh flat-top cell (logic power) |
| J1 | 5.5×2.1mm barrel jack (12V charge port) |
| J2 | USB-C panel jack (18650 charge port) |
| SW1 | SPST rocker switch with 12V LED |
| F1 | 5A ATC blade fuse + inline holder |
| U2 | ESP32-S3 Super Mini |
| U3 | TP4056 USB-C charger module with protection |
| U4 | MT3608 boost converter (3.7V → 5.0V) |
| K1 | 4-channel optocoupler-isolated relay module |
| D1 | 5mm green LED (status) |
| R1 | 330Ω ¼W resistor |
| D2–D5 | P6KE15A TVS diodes (one per output channel) |
| C1 | 100µF 25V electrolytic (5V bus decoupling) |
| C2–C5 | 0.1µF ceramic (relay IN pin decoupling) |
| BT1–BT4 | 4mm banana binding post pairs |

---

## Wiring Details

### Logic Power Chain

```
[B2 18650 cell]
  B+ ──► TP4056 (B+)
  B− ──► TP4056 (B−) ──► GND BUS

TP4056 OUT+ ──► MT3608 IN+
TP4056 OUT− ──► MT3608 IN− ──► GND BUS

MT3608 OUT+ ──► 5V BUS  ← pre-set to 5.00V before connecting ESP32
MT3608 OUT− ──► GND BUS

5V BUS ──► ESP32-S3 (5V pin)
5V BUS ──► Relay K1 (VCC)
GND BUS ──► ESP32-S3 (GND)
GND BUS ──► Relay K1 (GND)
```

### 12V Switching Chain

```
[B1 LiFePO4]
  BAT+ ──► SW1 ──► F1 ──► 12V BUS
  BAT− ──► GND BUS
  BAT+ ──► J1 charge port (bypasses SW1)

12V BUS ──► Relay K1 (JD-VCC)   ← jumper removed — see critical note
12V BUS ──► Relay K1 (COM×4)    ← all four COM terminals
```

### Relay Outputs (×4, identical)

```
Relay NO1 ──► TVS D2 (cathode/stripe) ──► BT1 red post (+)
              TVS D2 (anode)           ──► BT1 black post (−)
BT1 black post (−) ──► GND BUS
```

### ESP32 GPIO Assignments

| GPIO | Function |
|------|----------|
| GPIO4 | Relay K1 IN1 (Channel 1) |
| GPIO5 | Relay K1 IN2 (Channel 2) |
| GPIO6 | Relay K1 IN3 (Channel 3) |
| GPIO7 | Relay K1 IN4 (Channel 4) |
| GPIO2 | Status LED D1 (via R1 330Ω) |

### Status LED

```
ESP32 GPIO2 ──► R1 (330Ω) ──► D1 anode
                              D1 cathode ──► GND BUS
```

---

## Critical Notes

### ⚠ Relay JD-VCC Jumper — Must Remove

Most 4-channel relay modules ship with a jumper connecting VCC and JD-VCC. **Remove this jumper before use.**

- **Jumper ON:** relay coil powered from ESP32 5V rail — no isolation, spikes can damage ESP32
- **Jumper OFF:** relay coil powered separately via JD-VCC pin — optocoupler provides full electrical isolation

Wire JD-VCC directly to the 12V bus (not through the fuse — the relay coil draws ~70mA per channel, well within limits).

### ⚠ MT3608 Pre-adjustment

Before connecting the ESP32 or relay module:

1. Connect B2 (18650) to TP4056 — if the cell is fresh you may need to plug in USB-C first to activate the protection circuit
2. Power the MT3608 from TP4056 OUT+/OUT−
3. Measure MT3608 output with a multimeter
4. Adjust the trimmer pot until output reads **5.00V ± 0.05V**
5. Only then connect the ESP32 and relay VCC

Over-voltage will damage the ESP32-S3.

### ⚠ Shared GND

Both power domains share a common GND reference on the PCB. Connect TP4056 GND and LiFePO4 negative to the same GND bus. Do not float either ground.

### Relay Active-LOW Logic

The relay module is **active-LOW** — a GPIO driven LOW turns the relay ON, HIGH turns it OFF. All relay outputs default to HIGH (OFF) at boot in firmware. Confirm this behavior with your specific module before connecting devices.

### TVS Diode Orientation

P6KE15A is unidirectional. The **cathode (stripe end)** connects to the positive binding post (+). The anode connects to the negative post (−). Reversed orientation will short the output.

---

## Wire Gauge Guide

| Rail | Gauge | Reason |
|------|-------|--------|
| 12V power bus | 18 AWG | Fused at 5A, short runs |
| 12V output to binding posts | 18 AWG | Up to 2A momentary |
| 5V logic bus | 22 AWG | Low current, ESP32 + relay coils |
| GPIO signal lines | 24 AWG | Signal only, negligible current |
| GND bus | 18 AWG | Shared return for both domains |
