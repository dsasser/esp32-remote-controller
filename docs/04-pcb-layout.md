# 04 — PCB Layout

## Using ElectroCookie Boards

This design uses ElectroCookie solderable breadboard PCBs rather than a custom-fabricated board. The ElectroCookie format provides pre-routed power rails, a 5V bus, GND bus, and an ESP32 footprint — eliminating most of the custom layout work.

If you have the **snap-apart grid sheet** style, cut a section approximately 100mm × 80mm. If you have the **ESP32 Mini solderable board**, use it directly — the form factor fits the Hammond enclosure with room to spare.

---

## Zone Map

Divide the board into functional zones and populate in this order:

```
┌─────────────────────────────────────────────────────┐
│  ZONE 1         │  ZONE 2              │  ZONE 3    │
│  Battery conn.  │  Fuse F1 + SW1 conn  │  Charge J1 │
│  XT60 or screw  │  (wires to panel)    │  (to panel)│
├─────────────────┴──────────┬────────────────────────┤
│  ZONE 4                    │  ZONE 5                │
│  TP4056 + MT3608           │  ESP32-S3 Super Mini   │
│  18650 logic power chain   │  (on female headers)   │
├────────────────────────────┴───────────┬────────────┤
│  ZONE 6                                │  ZONE 7    │
│  Relay module K1                       │  Output    │
│  (on female headers, removable)        │  terminals │
│                                        │  to posts  │
├────────────────────────────────────────┴────────────┤
│  GND copper pour / GND bus trace runs full width    │
└─────────────────────────────────────────────────────┘
```

---

## Placement Rules

### Power Components

- Place F1 fuse holder and SW1 wiring at the **first point** after BAT+. Nothing on the 12V rail before the fuse.
- TP4056 and MT3608 should sit close together — the wire between TP4056 OUT+ and MT3608 IN+ carries 18650 discharge current and should be short.
- C1 (100µF decoupling cap) mounts as close as possible to the ESP32 5V pin — within 10mm ideally.
- C2–C5 (0.1µF) mount one per relay IN pin, within 10mm of each.

### ESP32-S3 Super Mini

- Mount on **female 2.54mm headers** — board plugs in and out without soldering.
- Orient the board so the USB-C port faces toward the rear of the enclosure or is accessible via a short USB-C panel extension cable for firmware flashing.
- Keep 5mm clearance around the WiFi/BLE antenna end of the board — no copper pour underneath the antenna overhang.

### Relay Module K1

- Mount on **female 2.54mm headers** — fully removable for replacement.
- Position so the relay output screw terminals (COM/NO/NC) face toward the output side of the enclosure.
- The 5V VCC/GND/IN pins face the ESP32 side.

### Output Wiring

- Run 18 AWG wire from relay NO terminals directly to the binding posts — do not route through the PCB for these high-current lines if possible.
- TVS diodes D2–D5 mount as close to the binding post terminals as the layout allows — their job is to clamp spikes at the output.

---

## Trace / Wire Sizing

| Connection | Size | Notes |
|-----------|------|-------|
| 12V bus | 18 AWG or 20mil PCB trace | Fused at 5A |
| 12V relay output | 18 AWG wire (not PCB trace) | Direct to binding posts |
| 5V logic bus | 22 AWG or 15mil PCB trace | ESP32 + relay coils |
| GPIO signals | 24 AWG or 10mil PCB trace | Signal only |
| GND bus | 18 AWG or copper pour | Common return |

---

## Module Mounting

All major modules mount on 2.54mm pin headers — **nothing is soldered directly to the board except passives and wiring terminals.** This means every module (ESP32, relay, TP4056, MT3608) can be replaced without desoldering.

```
Board (female header)
  └── Module (male header pins)
```

For the TP4056 and MT3608 which are small bare modules, solder short male header pins to their pads and use corresponding female headers on the board, or use small screw terminal blocks for the IN/OUT connections.

---

## Internal Stacking Order

The Hammond 1455N1601BK gives ~45mm of usable internal height. The layout stacks as follows:

```
Top (enclosure lid)
─────────────────────────────────────
  relay module (tallest component ~20mm with housing)
  ESP32-S3 Super Mini on headers
  ElectroCookie PCB (~2mm)
  PCB standoffs (~5mm) mounted to enclosure floor rails
─────────────────────────────────────
  LiFePO4 battery (~30mm tall, sits beside PCB)
  18650 holder (flat, mounted to board or enclosure floor)
─────────────────────────────────────
Bottom (enclosure floor / internal PCB rails)
```

The LiFePO4 battery sits alongside the PCB rather than under it — the Hammond enclosure internal width of ~95mm gives room for a ~60mm wide battery beside an ~80mm wide PCB.

Secure the LiFePO4 battery with a strip of hook-and-loop (Velcro) to the enclosure floor. Secure the 18650 holder with double-sided foam tape or a small 3D-printed bracket.

---

## PCB Fabrication Option

If you prefer a custom PCB over ElectroCookie:

- **Board size:** 100mm × 80mm recommended
- **Layers:** 2-layer FR4, 1oz copper
- **Surface finish:** HASL or ENIG
- **Holes:** 4× M3 mounting holes at corners
- **Software:** KiCad (free) — ESP32-S3 Super Mini footprint available in community libraries

JLCPCB or OSHPark will fabricate 5 copies for under $15 shipped.
