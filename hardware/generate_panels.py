#!/usr/bin/env python3
"""Generate the 3D-printable enclosure panels as solids for Autodesk Fusion.

Builds B-rep solids with CadQuery (OpenCASCADE) and exports STEP + STL for both
panels. Hole sizes carry PETG tolerance compensation (tuned for a 0.4mm nozzle).
The 2D profiles in front_panel.dxf / rear_panel.dxf use the *nominal* sizes for
laser-cut aluminum; this script uses the *printed* sizes.

Usage:
    pip install cadquery
    python hardware/generate_panels.py          # writes *.step and *.stl beside this file

Change THICKNESS below and re-run to re-size the panel — this file is the
parametric source for the printed panels.
"""
import os
import cadquery as cq

HERE = os.path.dirname(os.path.abspath(__file__))

# ---- parameters ------------------------------------------------------------
THICKNESS   = 2.0        # panel thickness (mm). ~1.5 to slide into the Hammond grooves; 2-3 to bolt on.
LABEL_DEPTH = 0.4        # debossed label depth on the front (+Z) face

# ---- shared geometry (mm) — matches the DXFs -------------------------------
PW, PH   = 103.0, 53.0
CORNERS  = [(5,5),(98,5),(5,48),(98,48)]
COL_X    = [18.5,40.5,62.5,84.5]
ROW_POS, ROW_NEG = 36.5, 16.5
LED_XY   = (94.0,26.5)
CHARGE_XY= (52.0,26.5)
USB_XY   = (87.0,26.5)

# printed hole radii = nominal + PETG compensation
# (M3 3.0->3.2, post 8.0->8.4, LED 5.0->5.2, barrel 12.0->12.4, USB M11 11.5->11.9)
R_M3, R_POST, R_LED, R_BARREL, R_USB = 1.6, 4.2, 2.6, 6.2, 5.95


def base():
    return cq.Workplane("XY").box(PW, PH, THICKNESS, centered=(False, False, False))

def drill(part, holes):
    for x, y, r in holes:
        part = part.cut(cq.Workplane("XY").cylinder(THICKNESS + 2, r).translate((x, y, THICKNESS / 2)))
    return part

def deboss(part, labels):
    """Recess labels into the top (+Z) face. Returns (part, ok)."""
    try:
        wp = part.faces(">Z").workplane()
        for x, y, size, txt in labels:
            wp = wp.moveTo(x - PW / 2, y - PH / 2).text(txt, size, -LABEL_DEPTH,
                                                        combine='cut', kind='bold')
        return wp, True
    except Exception as e:
        print("  labels skipped:", e)
        return part, False

def write(part, stem):
    cq.exporters.export(part, os.path.join(HERE, f"{stem}.step"))
    cq.exporters.export(part, os.path.join(HERE, f"{stem}.stl"))


# ---- front -----------------------------------------------------------------
front_holes  = [(cx, cy, R_M3) for cx, cy in CORNERS]
front_holes += [(x, y, R_POST) for x in COL_X for y in (ROW_POS, ROW_NEG)]
front_holes += [(LED_XY[0], LED_XY[1], R_LED)]
front_labels = [(x, 45.5, 2.5, f"CH{i+1}") for i, x in enumerate(COL_X)]
front_labels += [(x - 6.5, ROW_POS, 2.0, "+") for x in COL_X]
front_labels += [(x - 6.5, ROW_NEG, 2.0, "-") for x in COL_X]
front_labels += [(LED_XY[0], 31.5, 1.8, "STATUS"), (PW / 2, 4.0, 2.5, "IGNITER CONTROLLER")]
front, ok = deboss(drill(base(), front_holes), front_labels)
write(front, "front_panel")
print(f"front_panel: {len(front_holes)} holes, labels={ok}")

# ---- rear ------------------------------------------------------------------
rear_holes  = [(cx, cy, R_M3) for cx, cy in CORNERS]
rear_holes += [(CHARGE_XY[0], CHARGE_XY[1], R_BARREL), (USB_XY[0], USB_XY[1], R_USB)]
rear_labels = [(CHARGE_XY[0], 36.0, 2.0, "CHARGE"), (USB_XY[0], 36.0, 2.0, "USB-C"),
               (PW / 2, 4.0, 2.5, "IGNITER CONTROLLER")]
rear, ok = deboss(drill(base(), rear_holes), rear_labels)
write(rear, "rear_panel")
print(f"rear_panel: {len(rear_holes)} holes, labels={ok}")
print(f"done — wrote STEP + STL at THICKNESS={THICKNESS}mm")
