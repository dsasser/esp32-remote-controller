# 02 — Bill of Materials

All prices are estimates as of mid-2026. Most multi-packs leave useful spares.

---

## Core Modules

| Ref | Component | Spec | Link | Est. Price | Qty |
|-----|-----------|------|------|------------|-----|
| U2 | ESP32-S3 Super Mini | BLE 5.0, WiFi, USB-C, compact | [Amazon](https://www.amazon.com/s?k=ESP32-S3+Super+Mini+development+board) | ~$8 | 1 |
| K1 | 4-channel relay module | Optocoupler isolated, 5V logic, 10A contacts | [Amazon B0D3Y112J7](https://www.amazon.com/gp/product/B0D3Y112J7) | ~$8 | 1 |

---

## Logic Power (18650 path)

| Ref | Component | Spec | Link | Est. Price | Qty |
|-----|-----------|------|------|------------|-----|
| B2 | 18650 cell | Flat top, ~3000mAh — see note below | See note | ~$8–12 | 1 |
| — | 18650 cell holder | Single slot, wire leads | [Amazon B0BJV7SK5D](https://www.amazon.com/dp/B0BJV7SK5D) | ~$6 (10-pack) | 1 |
| U3 | TP4056 charger module | USB-C input, 5V/1A, with dual protection | [Amazon B08X6G26Q8](https://www.amazon.com/dp/B08X6G26Q8) | ~$8 (15-pack) | 1 |
| U4 | MT3608 boost converter | 3.7V → 5.0V adjustable, 2A | [Amazon B0BGLGL9RV](https://www.amazon.com/dp/B0BGLGL9RV) | ~$8 (10-pack) | 1 |
| J2 | USB-C panel jack | Panel-mount female, for 18650 charging | [Amazon — search "USB-C panel mount female"](https://www.amazon.com/s?k=usb+c+panel+mount+female+connector) | ~$7 (5-pack) | 1 |

> **18650 cell note:** Amazon is flooded with fake capacity cells. Buy from a trusted source:
> - [18650batterystore.com](https://www.18650batterystore.com) — Samsung 30Q 3000mAh (~$8) or Sanyo NCR18650GA 3450mAh (~$9)
> - [imrbatteries.com](https://imrbatteries.com) — same reliable cells
> - Get **flat top** (not button top) — works with standard holders
> - Avoid anything on Amazon claiming 5000mAh+

---

## 12V Switching Power

| Ref | Component | Spec | Link | Est. Price | Qty |
|-----|-----------|------|------|------------|-----|
| B1 | LiFePO4 battery | 12.8V 6Ah, built-in BMS | [Amazon B0DG1MZ88B](https://www.amazon.com/dp/B0DG1MZ88B) | ~$28 | 1 |
| — | LiFePO4 charger | 14.6V / 3A CC/CV smart charger, auto-shutoff | [Amazon B0991X3CW3](https://www.amazon.com/dp/B0991X3CW3) | ~$22 | 1 |
| SW1 | Master rocker switch | SPST 12V LED indicator, panel-mount | [Amazon — search "SPST rocker switch 12V LED 20mm panel"](https://www.amazon.com/s?k=SPST+rocker+switch+12V+LED+panel+mount+20mm) | ~$8 (5-pack) | 1 |
| F1 | ATC fuse holder + fuses | 12 AWG inline waterproof, assorted 1A–30A fuses | [Amazon B0CN6TVHKH](https://www.amazon.com/dp/B0CN6TVHKH) | ~$13 | 1 |
| J1 | 12V charge port | 5.5×2.1mm panel-mount barrel jack, dustproof cap | [Amazon B0BD46CP5Y](https://www.amazon.com/dp/B0BD46CP5Y) | ~$9 (6-pack) | 1 |

> **Fuse rating:** Install a 5A fuse for normal use (sequential firing). If simultaneously firing multiple channels, step up to 10A.

> **Charger note:** The LiFePO4 charger must be rated for LiFePO4 chemistry specifically — 14.6V CC/CV. A standard lithium or lead-acid charger will damage the battery or undercharge it.

---

## Protection

| Ref | Component | Spec | Link | Est. Price | Qty |
|-----|-----------|------|------|------------|-----|
| D2–D5 | TVS diodes | P6KE15A, 600W 15V unidirectional, DO-15 axial | [Amazon B0DNYJRYWJ](https://www.amazon.com/dp/B0DNYJRYWJ) | ~$8 (20-pack) | 4 |

---

## Output Connectors

| Ref | Component | Spec | Link | Est. Price | Qty |
|-----|-----------|------|------|------------|-----|
| BT1–BT4 | Banana binding post pairs | 4mm panel-mount, red + black, gold-plated | [Amazon B07KG11GL3](https://www.amazon.com/dp/B07KG11GL3) | ~$10 (40-pack) | 8 posts |

---

## Enclosure

| Ref | Component | Spec | Link | Est. Price |
|-----|-----------|------|------|------------|
| ENC | Hammond 1455N1601BK | 160×103×53mm, black anodized aluminum, IP54 | [Amazon B005S3MICW](https://www.amazon.com/dp/B005S3MICW) | ~$33 |

> **Why the N-series:** The L-series (1455L1601BK) is only 30.5mm tall internally — not enough clearance for the LiFePO4 battery plus PCB. The N-series at 53mm gives ~45mm usable internal height.

---

## Passive Components

Order as assortment kits if you don't already stock them.

| Ref | Component | Spec | Qty |
|-----|-----------|------|-----|
| R1 | Resistor | 330Ω ¼W through-hole | 1 |
| D1 | LED | 5mm green diffused, ~20mA | 1 |
| C1 | Electrolytic capacitor | 100µF 25V radial | 1 |
| C2–C5 | Ceramic capacitor | 0.1µF (104) | 4 |

| Kit | Link | Est. Price |
|-----|------|------------|
| Resistor assortment 525pcs | [Amazon B0792M83JH](https://www.amazon.com/dp/B0792M83JH) | ~$10 |
| LED assortment | [Amazon — search "5mm LED assortment 100pcs"](https://www.amazon.com/s?k=5mm+LED+assortment+100pcs) | ~$7 |
| Capacitor assortment | [Amazon — search "capacitor assortment electrolytic ceramic"](https://www.amazon.com/s?k=capacitor+assortment+electrolytic+ceramic) | ~$12 |

---

## Wire and PCB Materials

| Item | Spec | Est. Price | Notes |
|------|------|------------|-------|
| 18 AWG hookup wire | Stranded, red/black | ~$12 | 12V power and output rails |
| 22 AWG hookup wire | Stranded, multi-color | ~$10 | GPIO signal lines, 5V logic |
| ElectroCookie PCB | Solderable breadboard, ESP32 footprint | Existing | Use your existing board |
| 2.54mm pin headers | Male + female strips | ~$7 | For socketing all modules |
| Screw terminal blocks | 2-pin 3.5mm pitch | ~$8 (20-pack) | Power input connections |
| Solder | 63/37 or 60/40 rosin core, 0.8mm | ~$12 | — |

---

## Total Estimated Cost

| Category | Est. Cost |
|----------|-----------|
| Core modules | ~$16 |
| Logic power (18650 path) | ~$39 |
| 12V switching power | ~$52 |
| Protection | ~$8 |
| Output connectors | ~$10 |
| Enclosure | ~$33 |
| Passives + wire + solder | ~$49 |
| **Total** | **~$207** |

*ElectroCookie PCB not included — using existing stock.*
