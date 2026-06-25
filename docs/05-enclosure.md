# 05 — Enclosure

## Hammond 1455N1601BK

**External:** 160mm L x 103mm W x 53mm H
**Internal usable depth:** ~45mm
**Material:** Extruded aluminum, black anodized, IP54
**End panels:** Removable aluminum, 103 x 53mm each

Front and rear panels are custom-cut by **SendCutSend** from the DXF files in `/hardware`.

---

## Revision after first fabrication

The first set of panels came back from SendCutSend with three fit problems against the real parts:

1. **Binding-post nuts collided.** The two posts in each pair were only 10mm apart center-to-center; the mounting nuts/washers overlap and can't both seat.
2. **Fuse slot was unusable.** The 20×13mm slot assumed a panel-mount blade fuse holder, but the fuse in the BOM is an **inline pigtail holder** that has no flange or thread to mount through a panel at all.
3. **USB-C opening was too small.** The 9×3.5mm slot fit only a bare USB-C *plug*, not a panel-mount USB-C *receptacle*. It's now a **∅11.5mm round hole** for an M11×1.0 threaded receptacle (J2) whose nut clamps any panel thickness.

The DXFs in `/hardware` are the **corrected revision**:

| Panel feature | Size | Resolution |
|---------------|------|------------|
| Front: 8× ∅8mm holes | 8mm | Binding posts re-laid as a **2-row grid** (4 columns @ 22mm pitch, +/− rows 20mm apart) so nuts clear — min 20mm center-to-center |
| Front: ∅5mm hole | 5mm | Status LED — moved to the right edge, vertically centered |
| Rear: ∅12mm round hole | 12mm | DaierTek barrel jack — unchanged, correct size |
| Rear: ~~20×13mm fuse slot~~ | — | **Removed.** Inline fuse holder now lives inside the enclosure |
| Rear: ∅12mm round hole | 12mm | **Master power switch (SW1)** restored — see note below |
| Rear: USB-C cutout | **∅11.5mm round** | M11×1.0 threaded panel-mount USB-C, nut-clamped (was 9×3.5mm) |
| Both: 4× ∅3mm corner holes | 3mm | M3 panel mounting — unchanged |

> The rear USB-C receptacle preserves wired firmware flashing and serial debug access to the ESP32-S3 Super Mini. It's an **M11×1.0 threaded mount**: the barrel passes through the ∅11.5mm hole and a hex nut clamps from behind, so it seats solidly in panels of any thickness. Its 4-wire pigtail plugs into the ESP's USB pads internally.

> **Master power switch (SW1) restored.** The original design had a panel master switch, but it was lost when the design consolidated to 2S — its rear slot was relabeled as the fuse cutout and then removed. It's back as a **∅12mm round hole at X=22mm**, giving a symmetric POWER / CHARGE / USB-C layout. A master cutoff is *more* important in the 2S design: the pack feeds the boost continuously, so without it the ESP32 is always drawing current, and switching it off de-energizes the firing rail (the binding posts go dead). See [03-schematic.md](03-schematic.md).

> The 5A fuse is now an **inline holder wired into the battery+ lead inside the box** (see [02-bom.md](02-bom.md)). The rear panel carries no fuse cutout. To restore panel-accessible fuse swaps, switch to a round-bezel panel-mount holder and add a ∅12mm hole to `rear_panel.dxf`.

---

## Panel Elevations

These elevations are generated directly from the `/hardware` DXF coordinates, so they are true to scale (1:1 in mm). `CUT` features are red, `ENGRAVE` labels blue, dimensions gray.

**Front panel** — 4 binding-post pairs (CH1–CH4) in a 2-row grid, status LED, 4× M3 corner holes:

![Front panel elevation](images/front-panel.svg)

**Rear panel** — power switch, charge jack, USB-C cutout, 4× M3 corner holes (no fuse slot):

![Rear panel elevation](images/rear-panel.svg)

---

## Front Panel Hole Positions

Posts sit in two rows: **+ (red) at Y = 36.5mm**, **– (black) at Y = 16.5mm**. Each channel is one column.

| Channel | Hole | Column X | + row Y | – row Y |
|---------|------|----------|---------|---------|
| CH1 | ∅8mm | 18.5mm | 36.5mm | 16.5mm |
| CH2 | ∅8mm | 40.5mm | 36.5mm | 16.5mm |
| CH3 | ∅8mm | 62.5mm | 36.5mm | 16.5mm |
| CH4 | ∅8mm | 84.5mm | 36.5mm | 16.5mm |
| Status LED | ∅5mm | 94.0mm | — (Y = 26.5mm) | |

Column pitch: 22mm. Row spacing (+ to –): 20mm. Minimum nut clearance: 20mm center-to-center.

## Rear Panel Hole Positions (Y = 26.5mm center)

| Feature | Hole | X position |
|---------|------|-----------|
| Power switch SW1 | ∅12mm | 22mm |
| Charge jack J1 | ∅12mm | 52mm |
| USB-C (J2, flashing) | ∅11.5mm round (M11 threaded mount) | 87mm |

---

## Fabrication Files

The panels can be **laser/waterjet cut from aluminum** (2D DXF) or **3D printed** (3D STEP/STL solids). Both come from one shared geometry definition, so the hole positions match.

**DXF (aluminum)** — `/hardware/front_panel.dxf` and `/hardware/rear_panel.dxf` carry *nominal* hole sizes across five layers:
- `CUT` (red) — holes and slots
- `ENGRAVE` (blue) — labels
- `OUTLINE` (black) — panel boundary, reference only
- `DIMENSION` (gray) — measurements, reference only
- `CENTERLINE` (green, dashed) — hole crosshairs, reference only

These import directly into SendCutSend, Front Panel Express, or any CAD/CAM tool.

**STEP / STL (3D print)** — `/hardware/front_panel.step` and `/hardware/rear_panel.step` are the panels as **solid bodies** with PETG-compensated holes and debossed labels. In **Autodesk Fusion**, bring the STEP in via **File → Open** (or upload it to the project) — it lands as a native, editable solid you can tweak with push/pull. The matching `.stl` files (`Insert → Insert Mesh`, or straight into a slicer) are ready to print as-is.

> **Changing thickness:** the solids are built by `/hardware/generate_panels.py` (CadQuery). Edit `THICKNESS` at the top and re-run (`pip install cadquery && python hardware/generate_panels.py`) to regenerate both STEP + STL. That script is the parametric source — easier than push/pulling the body in Fusion, though either works.

---

## 3D-Printed Panels

The STEP/STL solids default to a **2mm** panel. Pick thickness by how the panel attaches:

- **~1.5mm** to slide into the Hammond extrusion's grooves (matches the stock aluminum panel).
- **2–3mm** for a stiffer panel bolted on through the four M3 corner holes.

> Every panel-mount part here clamps with a nut or threaded body — binding posts, the rocker switch (SW1), barrel jack, and the **M11×1.0 threaded USB-C** (J2). They all seat in any printed thickness, so there's no thin-wall snap-fit to design around. The USB-C thread is ~14.5mm long, plenty for a 2–3mm panel.

### Hole tolerances

Baked into the STEP/STL solids for black PETG on a 0.4mm nozzle. If your printer runs tight, bump the radii in `generate_panels.py` and re-run.

| Feature | Nominal | Printed |
|---------|---------|---------|
| M3 corner hole | ∅3.0mm | ∅3.2mm |
| Binding post | ∅8.0mm | ∅8.4mm |
| Status LED | ∅5.0mm | ∅5.2mm |
| Power switch / barrel jack | ∅12.0mm | ∅12.4mm |
| USB-C (M11 thread) | ∅11.5mm | ∅11.9mm |

### Print settings

| Setting | Value |
|---------|-------|
| Material | Black PETG |
| Layer height | 0.15mm |
| Infill | 40% |
| Orientation | Front (labeled) face down — best surface on the visible side |

---

## Panel Labeling

For now a label maker works fine. For a professional finish, the DXF `ENGRAVE` layer can be sent to SendCutSend (engraving) or Front Panel Express for laser-engraved, anodized labels.

Suggested labels: CH1-CH4 above each binding-post column, "CHARGE" by the barrel jack, "USB-C" by the rear USB cutout, polarity + / - marks per post. (The fuse is internal, so it needs no panel label.)

---

## Internal Mounting

- **PCB:** M3 standoffs to the floor, or slide into the enclosure's internal rails
- **Relay module:** bolted flat to the floor via M3 through its corner holes
- **2S pack:** hook-and-loop strap to the floor so it can't shift
- **Inline fuse holder:** wired into the battery+ lead and tucked inside the box (zip-tied to the floor or harness); open the enclosure to swap the fuse
- **Barrel jack + USB-C receptacle:** panel-mounted on the rear, wired with enough slack to swing the panel open ~45 deg for servicing
