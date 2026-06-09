# 05 — Enclosure

## Hammond 1455N1601BK

**External dimensions:** 160mm L × 103mm W × 53mm H
**Internal usable depth:** ~45mm
**Material:** Extruded aluminum, black anodized
**IP rating:** IP54 (dust and splash resistant)
**End panels:** Removable aluminum, 103mm × 53mm each

The end panels come off completely by removing four small Phillips screws. Do all drilling on the bench before installing any internal components.

DXF files for both panels are in `/hardware/` and ready to submit to Front Panel Express or any laser/CNC service.

---

## Front Panel Layout

The front panel faces the operator and carries all output connections.

```
┌─────────────────────────────────────────────────────────────────┐
│                                                        ● STATUS │
│                                                                  │
│    CH1          CH2          CH3          CH4                   │
│  ●(+) ●(-)   ●(+) ●(-)   ●(+) ●(-)   ●(+) ●(-)               │
│                                                                  │
│              REMOTE CONTROLLER                                   │
└─────────────────────────────────────────────────────────────────┘
```

### Front Panel Hole Positions (all Y = 26.5mm from bottom)

| Feature | Hole | X position | Y position |
|---------|------|-----------|-----------|
| CH1 + (red) | ∅8mm | 10.5mm | 26.5mm |
| CH1 − (black) | ∅8mm | 20.5mm | 26.5mm |
| CH2 + (red) | ∅8mm | 34.5mm | 26.5mm |
| CH2 − (black) | ∅8mm | 44.5mm | 26.5mm |
| CH3 + (red) | ∅8mm | 58.5mm | 26.5mm |
| CH3 − (black) | ∅8mm | 68.5mm | 26.5mm |
| CH4 + (red) | ∅8mm | 82.5mm | 26.5mm |
| CH4 − (black) | ∅8mm | 92.5mm | 26.5mm |
| Status LED | ∅5mm | 94.0mm | 43.0mm |
| Corner screws (×4) | ∅3mm | 5mm from each corner | 5mm from each corner |

Post spacing within each pair: **10mm** center-to-center
Gap between channel pairs: **14mm**

---

## Rear Panel Layout

The rear panel carries power management connections.

```
┌─────────────────────────────────────────────────────────────────┐
│                                                                  │
│   ┌──────────┐        ◯              ┌───────────┐             │
│   │  POWER   │    12V CHARGE         │ USB-C CHG │             │
│   │  SWITCH  │    (LiFePO4)          │  (18650)  │             │
│   └──────────┘                       └───────────┘             │
│                                                                  │
│              REMOTE CONTROLLER                                   │
└─────────────────────────────────────────────────────────────────┘
```

### Rear Panel Hole Positions

| Feature | Hole | X position | Y position |
|---------|------|-----------|-----------|
| Master switch SW1 | 20×13mm slot | 22mm center | 26.5mm center |
| 12V charge port J1 | ∅12mm | 52mm center | 26.5mm center |
| USB-C charge port J2 | 9×3.5mm slot | 87mm center | 26.5mm center |
| Corner screws (×4) | ∅3mm | 5mm from each corner | 5mm from each corner |

---

## Drilling Instructions

### Tools Required

| Tool | Use |
|------|-----|
| Step drill bit (4–22mm) | All round holes — 5mm, 8mm, 12mm in one tool |
| Center punch | Mark every hole before drilling |
| Painter's tape | Cover panel surface to prevent scratches |
| Hand file or rotary tool | Rectangular slots (switch, USB-C) |
| Countersink bit | Deburr all holes after drilling |
| Ruler and marker | Transfer measurements |

### Procedure

1. Print the DXF at 1:1 scale on paper (verify with ruler before using)
2. Tape the paper template to the panel, aligned with corners
3. Center punch through paper at every hole center
4. Remove paper template
5. Apply painter's tape over the panel face
6. Drill all round holes with step drill bit, working up through sizes
7. For rectangular slots: drill 4 corner holes, then file or nibble between them
8. Deburr all holes with countersink bit
9. Remove tape and clean panel

### Tips

- Clamp the panel firmly — aluminum grabs drill bits if the panel shifts
- Use cutting fluid or WD-40 on the drill bit for cleaner holes and longer bit life
- The step drill makes clean holes in thin aluminum without grabbing — preferred over twist bits for panel work
- For the rocker switch slot, a nibbling tool (cheap from Amazon) gives the cleanest result without a file

---

## Panel Labeling

### Option 1 — Label Maker (immediate)

A Dymo or Brother label maker with white text on clear or black tape works well. Print individual labels for each channel and the rear panel connectors. Not as crisp as engraving but perfectly functional.

Apply labels slightly above or below the holes so they're not obscured by the connectors.

### Option 2 — Front Panel Express (professional)

[frontpanelexpress.com](https://www.frontpanelexpress.com) — upload the DXF files from `/hardware/`, set material to black anodized aluminum, assign the `CUT` layer to machining and `ENGRAVE` layer to engraving. Expect ~$25–40 for both panels shipped. Lead time typically 1–2 weeks.

The result looks completely commercial — laser-engraved white text, precision-machined holes.

### Option 3 — Vinyl cut decal

Services like Sticker Mule or a local sign shop can cut white vinyl labels from the DXF artwork. Adhesive-backed, reasonably durable, lower cost than engraving.

---

## Internal Mounting

### PCB

The 1455N1601BK has extruded internal rails running the length of the enclosure body. These accept standard 100mm Eurocard PCBs sliding in horizontally. If your ElectroCookie board is close to 100mm wide, it may slide in directly. Otherwise use M3 standoffs screwed to the enclosure floor.

### LiFePO4 Battery

Secure with a 20mm wide hook-and-loop (Velcro) strap around the battery and through a pair of small holes in the enclosure floor, or use a strip of double-sided foam tape rated for the battery weight (~300g). The battery should not be able to shift during transport.

### 18650 Holder

Double-sided foam tape to the enclosure floor or a small 3D-printed bracket clipped to the PCB standoffs.

### Cable Management

- Keep 12V output wires (relay NO to binding posts) as short and direct as possible
- Twist the 12V power pair (BAT+ and BAT− from LiFePO4) loosely to reduce EMI
- Leave enough slack on panel-mounted component wires to allow the end panels to swing open ~45° for servicing

---

## 3D-Printed Parts

### Hole Tolerances

These radii are tuned for black PETG on a 0.4mm nozzle. Adjust ±0.1mm if your printer runs large or small.

| Feature | Nominal | Print radius | Print diameter |
|---------|---------|-------------|----------------|
| M3 mounting hole | M3 | r = 1.6mm | ∅3.2mm |
| Button hole | ∅8mm | r = 4.2mm | ∅8.4mm |
| LED hole | ∅5mm | r = 2.6mm | ∅5.2mm |
| Barrel jack hole | ∅12mm | r = 6.2mm | ∅12.4mm |

For rectangular cutouts (rocker switch, USB-C), add **+0.2mm clearance on all sides** relative to the connector's body dimension.

### Print Settings

| Setting | Value |
|---------|-------|
| Material | Black PETG |
| Layer height | 0.15mm |
| Infill | 40% |
| Orientation | Top face down (improves surface quality on the visible face) |
