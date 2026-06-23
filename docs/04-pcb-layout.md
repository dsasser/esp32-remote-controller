# 04 — PCB Layout

## Medium ElectroCookie — Three-Zone Layout

The build uses a **medium black ElectroCookie board (~80x60mm)**. The relay module mounts separately on the enclosure floor, keeping the board compact. Components organize into three left-to-right zones.

```
+--------------------------------------------------------------+
|  POWER IN (left)   |   LOGIC (center)      |  OUTPUT (right) |
|                    |                       |                 |
|  [BATT IN screw]   |  [ESP32-S3 on         |  [TVS D2]       |
|  [FUSE screw]      |   female headers]     |  [TVS D3]       |
|  [BARREL screw]    |                       |  [TVS D4]       |
|  [RELAY SIG screw] |  [MT3608 boost]       |  [TVS D5]       |
|  (6-wire ribbon)   |  [status LED tap]     |  [OUTPUT screw  |
|                    |                       |   terminals]    |
+--------------------------------------------------------------+
            GND rail / 7.4V rail run along board edges
```

---

## Zone Detail

### Left Zone — Power & External Connections
All screw terminals for things that leave the board:
- **BATT IN** — 7.4V from the 2S BMS (P+/P-)
- **FUSE** — out to / back from the panel-mount 5A blade fuse
- **BARREL** — charge jack connection (to BMS charge input)
- **RELAY SIGNAL** — 6-wire ribbon terminals (GND, 5V, IN1-4) to the off-board relay

### Center Zone — Logic
- **ESP32-S3 Super Mini** on two rows of female 2.54mm headers (the Super Mini is narrow — use 8-pin rows). Socketed so it lifts out.
- **MT3608 boost** — mount first, adjust to 5.0V before anything else is connected.
- Status LED tap point — GPIO2 through R1 out to a flying lead to the panel LED.

### Right Zone — Output
- **TVS diodes D2-D5** on the output side of the relay NO contacts, cathode toward the positive output.
- **Output screw terminals** to the four binding post pairs.

---

## Assembly Notes

1. The ESP32-S3 Super Mini is narrow — use two rows of 8-pin female headers.
2. Mount the MT3608 first and adjust it to 5.0V with a multimeter before connecting anything else. The pot is sensitive.
3. The relay module mounts separately on the Hammond's internal floor via M3 screws through its corner holes. Run a 6-wire ribbon (GND, 5V, IN1, IN2, IN3, IN4) from the relay signal terminals on the PCB to the relay board.
4. TVS diodes go on the output side of the relay NO contacts — between the relay and the binding posts. Cathode toward the positive output.
5. The LED lead needs to reach the front panel hole — solder a ~15cm wire extension with heat shrink on the joints.
6. Keep 7.4V power traces (battery, fuse, output) on one side of the board and 5V/signal on the other where possible, for noise isolation.
7. Use 18 AWG wire for all 7.4V power connections. 22 AWG is fine for 5V logic and GPIO signals.

---

## Internal Mounting

```
Hammond 1455N1601BK floor:
  - ElectroCookie PCB on M3 standoffs (or enclosure rails)
  - VNFOCKQSH relay module bolted flat to floor (M3)
  - 2S 18650 pack secured with hook-and-loop strap
  - Panel-mount fuse holder and barrel jack on rear panel
  - Binding posts and LED on front panel
```

The off-board relay and single battery pack leave plenty of room inside the enclosure. The 6-wire ribbon gives enough slack to lift the PCB out for servicing without disconnecting the relay.
