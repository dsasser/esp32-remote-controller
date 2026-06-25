# 01 — System Overview

## What This Is

A portable 4-channel remote igniter controller for **hobby rocketry**. It fires up to four Estes-type igniters wirelessly over BLE from a phone, delivering a momentary firing pulse to each channel independently. Built around the ESP32-S3 Super Mini in a Hammond 1455N1601BK anodized aluminum enclosure with custom SendCutSend panels.

---

## Design Goals

| Goal | How it's met |
|------|-------------|
| Portable and self-contained | Single internal 2S battery, no external power |
| Wireless control | ESP32-S3 BLE 5.0, ~30-100ft range |
| Safe firing | Relays default open, optocoupler isolation, TVS protection |
| Simple | One battery, one boost converter, minimal parts |
| Serviceable | Socketed ESP32, off-board relay, replaceable inline fuse |
| Professional finish | Hammond aluminum enclosure, SendCutSend panels |

---

## System Architecture

A single **2S Li-ion pack** (2× Samsung 30Q in series, 7.4V nominal) powers everything:

- **Firing power:** Raw 7.4V routes through a 5A fuse directly to the relay COM terminals. When a relay fires, 7.4V appears across the binding posts and fires the igniter. Estes igniters need only 0.5-1A, so 7.4V is entirely sufficient.
- **Logic power:** One MT3608 boost converter steps 7.4V up to a regulated 5.0V, powering both the ESP32-S3 and the relay module's coil/logic side.

This single-battery design replaced an earlier, more complex dual-battery architecture. The simplification was possible because hobby igniters are forgiving, low-current loads.

```
[Phone / BLE]
      | BLE
      v
[ESP32-S3 Super Mini] --GPIO4-7 via 6-wire ribbon--> [VNFOCKQSH Relay (off-board)]
      ^                                                      |
[MT3608 5V boost]                                      COM x4 <-- 7.4V (fused)
      ^                                                NO x4
[2S Pack: 2x Samsung 30Q]                                   |
[2S BMS] <-- 8.4V charger via DaierTek jack          [TVS D2-D5] + [Binding Posts]
                                                            |
                                                      [Igniters 1-4]
```

---

## Key Design Decisions

**Why 2S 18650 instead of a 12V pack?**
Estes igniters fire at 0.5-1A. The raw 7.4V from two series cells drives them directly — no need for a 12V switching supply or a separate logic battery. Two cells, one BMS, one boost converter. Lighter and simpler.

**Why the VNFOCKQSH relay module?**
Cheaper and faster-shipping than the original pick, with optocoupler isolation and a selectable H/L trigger jumper. The optocouplers protect the ESP32 GPIOs; the relay contacts handle output isolation. The JD-VCC jumper is removed.

**Why mount the relay off-board?**
Keeps the ElectroCookie PCB compact and uncluttered. The relay bolts to the Hammond's internal floor via M3 screws and connects back to the board with a 6-wire ribbon (GND, 5V, IN1-4). Easy to replace.

**Why BLE?**
No infrastructure needed — works anywhere at the launch site. Pairs in under a second. The firmware also has WiFi and ESP-NOW options roughed in.

---

## Specifications

| Parameter | Value |
|-----------|-------|
| Output channels | 4 |
| Output voltage | 7.4V (raw 2S cell voltage) |
| Igniter load | 0.5-1A typical (Estes-type) |
| Pulse duration | Configurable, default 1000ms |
| Wireless | BLE 5.0 (primary), WiFi / ESP-NOW (optional) |
| Battery | 2S — 2x Samsung 30Q 18650, 7.4V ~3000mAh |
| BMS | 2S Li-ion protection, 10A+ |
| Charging | 8.4V wall charger via DaierTek barrel jack |
| Output connectors | 4mm banana binding posts, 4 pairs |
| Enclosure | Hammond 1455N1601BK, 160x103x53mm |
| Microcontroller | ESP32-S3 Super Mini |
| Relay | VNFOCKQSH 5V 4-channel, optocoupler isolated |
| Protection | TVS diodes, optocoupler isolation, 5A fuse, 2S BMS |

---

## Safety Notes

This device fires pyrotechnic igniters. Observe standard rocketry safety:

- Relays default to open (safe) on power-up
- Keep the system unpowered until ready to fire
- Maintain safe distance per NAR/Tripoli guidelines
- The momentary-pulse firmware prevents a stuck-on output
- TVS diodes clamp inductive spikes from the igniter bridgewire
