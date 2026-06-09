# 01 — System Overview

## What This Is

A portable 4-channel remote controller that delivers momentary 12V / 2A pulses to external devices via relay switching, controlled wirelessly over BLE from a phone or dedicated handset. The design prioritizes clean construction, full serviceability, and a professional finish in an aluminum enclosure.

The closest analogy is an electronic match controller — but the design is general-purpose and safe for any application needing remotely-triggered momentary 12V outputs.

---

## Design Goals

| Goal | How it's met |
|------|-------------|
| Portable and self-contained | Two internal batteries, no external power needed |
| Wireless control | ESP32-S3 BLE 5.0, ~30–100ft range |
| Safe switching | Optocoupler-isolated relay module, TVS spike protection |
| Serviceable | All modules socket-mounted on headers, blade fuse |
| Professional finish | Hammond anodized aluminum enclosure, DXF panel files |
| Open source friendly | All design files, firmware, and docs in this repo |

---

## System Architecture

The design splits into two completely separate power domains:

**12V switching domain** — a 12.8V 6Ah LiFePO4 battery feeds the relay COM terminals directly through a master switch and 5A fuse. When a relay fires, 12V appears across the corresponding binding post pair for the duration of the pulse. Nothing else in the box runs from this rail except the relay coil JD-VCC line.

**5V logic domain** — a single 18650 cell charges via USB-C through a TP4056 module. Its output feeds an MT3608 boost converter set to 5.0V, which powers the ESP32-S3 and the relay module's logic side. This domain is entirely independent — the box can be programmed, tested, and BLE-connected with the 12V battery disconnected.

The two GND rails share a common reference point on the PCB, but no power crosses between domains.

```
[Phone / BLE handset]
        │ BLE
        ▼
[ESP32-S3 Super Mini] ─── GPIO4–7 ──► [4-ch Relay Module]
        │                                      │
[18650 + TP4056]                         COM × 4 ◄── [12V LiFePO4]
[MT3608 5V boost]                        NO × 4
                                              │
                              [TVS D2–D5] + [Binding Posts BT1–BT4]
                                              │
                                         [Devices 1–4]
```

---

## Key Design Decisions

**Why LiFePO4 for the switching battery?**
LiFePO4 chemistry is inherently stable — no thermal runaway, no puffing, safe in an enclosed metal box. The built-in BMS handles over/under-voltage. A 6Ah pack gives hundreds of momentary-use cycles before needing recharge.

**Why a separate 18650 for logic power?**
Avoids a buck converter, simplifies the PCB, and gives the ESP32 a completely clean power rail isolated from switching transients. The 18650 charges via USB-C independently of the main battery — two separate charge ports on the rear panel.

**Why optocoupler isolation on the relay module?**
The JD-VCC jumper is removed so the relay coil (12V side) is electrically isolated from the ESP32 GPIO pins. A voltage spike on the output side cannot reach the microcontroller.

**Why BLE over WiFi?**
No infrastructure required. The box works anywhere — field, garage, event venue — without needing a router or access point. BLE pairs in under a second and has sufficient range for the intended use. WiFi remains an option in the firmware if preferred.

**Why Hammond 1455N1601BK?**
Extruded aluminum construction, IP54 rated, anodized black finish, removable end panels for easy drilling, and it reads as professional test equipment rather than a hobby project. The N-series (53mm height) is required — the shorter L-series doesn't have enough internal clearance for the LiFePO4 battery.

---

## Specifications

| Parameter | Value |
|-----------|-------|
| Output channels | 4 |
| Output voltage | 12V (from LiFePO4 battery) |
| Max output current | 2A per channel (momentary) |
| Pulse duration | Configurable, default 1000ms |
| Wireless protocol | BLE 5.0 (primary), WiFi 2.4GHz (available) |
| BLE range | ~30–100ft (10–30m) line of sight |
| Logic supply | 18650 Li-ion, ~3000mAh |
| Logic battery life | 10–20+ hours per charge |
| Switching supply | LiFePO4 12.8V 6Ah |
| Switching cycles | 200+ per charge (1A avg, 1s pulse) |
| Output connectors | 4mm banana binding posts, 4 pairs |
| Enclosure | Hammond 1455N1601BK, 160×103×53mm |
| Enclosure material | Anodized aluminum, IP54 |
| Microcontroller | ESP32-S3 Super Mini |
| Relay rating | 10A / 250VAC (well above requirement) |
| Protection | TVS diodes, optocoupler isolation, 5A blade fuse, BMS |
