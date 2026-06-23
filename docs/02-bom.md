# 02 — Bill of Materials

4-channel remote igniter controller for hobby rocketry. Single 2S Li-ion battery architecture. Prices are estimates as of mid-2026.

---

## Core Modules

| Ref | Component | Spec | Sourcing | Est. Price | Qty |
|-----|-----------|------|----------|------------|-----|
| U2 | ESP32-S3 Super Mini | BLE 5.0, WiFi, USB-C, compact | Amazon — "ESP32-S3 Super Mini" | ~$8 | 1 |
| K1 | VNFOCKQSH 4-channel relay module | 5V, optocoupler isolated, H/L trigger jumper, 10A contacts | Amazon — "VNFOCKQSH 4 channel relay 5V" | ~$8 | 1 |
| U1 | MT3608 boost converter | Adjustable, 7.4V → 5.0V, 2A | Amazon — "MT3608 boost converter" | ~$8 (multi-pack) | 1 |

---

## Battery & Power

| Ref | Component | Spec | Sourcing | Est. Price | Qty |
|-----|-----------|------|----------|------------|-----|
| B1 | 18650 cells | Samsung 30Q 3000mAh, flat top — **2 in series** | [18650batterystore.com](https://www.18650batterystore.com) | ~$8 each (~$16) | 2 |
| — | 2S Li-ion BMS | 2S protection board, 10A+ | Amazon — "DIANN 2S BMS" | ~$6 | 1 |
| — | 2S charger | 8.4V wall charger, 5.5×2.1mm barrel plug | Amazon — "iCreatin 8.4V charger" | ~$10 | 1 |
| J1 | Charge jack | DaierTek panel-mount 5.5×2.1mm barrel jack | Amazon — "DaierTek panel mount barrel jack" | ~$8 (multi) | 1 |
| — | 18650 holder | 2-cell series holder or 2x single holders | Amazon | ~$6 | 1 |

> **Why 2S (7.4V)?** Estes hobby igniters fire reliably at 0.5-1A. The raw 7.4V cell voltage drives them directly through the relay contacts — no separate high-voltage switching supply needed. This single-battery architecture replaced an earlier dual-battery (12V LiFePO4 + 18650 logic) design, removing significant complexity.

> **Cell sourcing:** Buy Samsung 30Q from a reputable vendor like 18650batterystore.com or imrbatteries.com. Avoid Amazon cells claiming inflated capacities. Use flat-top cells for series holders.

> **Charging:** The 8.4V charger connects through the DaierTek barrel jack and charges the pack through the BMS. Single-port charging — no need to remove cells.

---

## Switching & Protection

| Ref | Component | Spec | Sourcing | Est. Price | Qty |
|-----|-----------|------|----------|----------|-----|
| F1 | Blade fuse + holder | 5A blade fuse, panel-mount holder (20x13mm cutout) | Amazon — "panel mount blade fuse holder" | ~$8 | 1 |
| D2–D5 | TVS diodes | P6KE15A, 600W 15V unidirectional, DO-15 axial | Amazon — "P6KE15A TVS diode" | ~$8 (20-pack) | 4 |

> **Fuse:** A 5A blade fuse protects the 7.4V rail. Mounted in a panel-accessible holder on the rear panel for easy replacement without opening the enclosure.

---

## Output Connectors

| Ref | Component | Spec | Sourcing | Est. Price | Qty |
|-----|-----------|------|----------|----------|-----|
| BT1–BT4 | Banana binding post pairs | 4mm panel-mount, red + black | Amazon — "Glarks banana binding post" | ~$10 (multi) | 8 posts |

> Hobby igniters connect via alligator clip leads that clip directly onto the banana posts. Convention: red = positive, black = negative per channel.

---

## PCB & Passives

| Ref | Component | Spec | Qty |
|-----|-----------|------|-----|
| — | ElectroCookie PCB | Medium black, ~80x60mm | 1 |
| R1 | Resistor | 330Ω ¼W | 1 |
| D1 | LED | 5mm green diffused | 1 |
| C1 | Electrolytic cap | 100µF 25V (5V bus decoupling) | 1 |
| C2–C5 | Ceramic cap | 0.1µF (relay IN decoupling) | 4 |
| — | Female pin headers | 2.54mm — socket the ESP32-S3 | 2 strips |
| — | Screw terminal blocks | 2-pin 3.5mm — power/signal/output | ~8 |
| — | Ribbon cable | 6-conductor, relay link | ~30cm |

---

## Enclosure

| Ref | Component | Spec | Sourcing | Est. Price |
|-----|-----------|------|----------|------------|
| ENC | Hammond 1455N1601BK | 160x103x53mm, black anodized aluminum, IP54 | Amazon B005S3MICW | ~$33 |
| — | Custom panels | Front + rear, SendCutSend (already fabricated) | DXF in `/hardware` | — |

> Front and rear aluminum panels were cut by SendCutSend using the DXF files in `/hardware`. Both panels are confirmed compatible with the 2S design — see [05-enclosure.md](05-enclosure.md).

---

## Total Estimated Cost

| Category | Est. Cost |
|----------|-----------|
| Core modules (ESP32-S3, relay, MT3608) | ~$24 |
| Battery & power (cells, BMS, charger, jack, holder) | ~$46 |
| Switching & protection (fuse, TVS) | ~$16 |
| Output connectors | ~$10 |
| PCB & passives | ~$20 |
| Enclosure | ~$33 |
| **Total** | **~$149** |

*ElectroCookie PCB and custom panels using existing/already-fabricated stock.*

---

## Changes From Previous Revision

This BOM reflects the **single 2S battery** architecture. Removed from earlier designs:

- ~~12.8V LiFePO4 battery~~ -> replaced by 2S 18650 pack
- ~~Separate 18650 + TP4056 logic supply~~ -> one pack now feeds both via MT3608
- ~~LiFePO4 14.6V charger~~ -> replaced by 8.4V 2S charger
- ~~Second MT3608 / buck converter~~ -> single MT3608 boost

The result is lighter, simpler, cheaper, and fully sufficient for hobby igniter loads.
