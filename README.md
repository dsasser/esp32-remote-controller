# ESP32-S3 4-Channel Remote Controller

A portable, wireless 4-channel remote controller built around the ESP32-S3 Super Mini. Designed to deliver momentary 12V / 2A pulses to four independently switched output channels via BLE or WiFi. Housed in a Hammond 1455N1601BK anodized aluminum enclosure.

> **Status:** Hardware design complete. Firmware in active development.

![Enclosure render placeholder](docs/images/enclosure_placeholder.png)

---

## Features

- 4 independently switched 12V output channels
- Up to 2A momentary current per channel (~1 second pulse)
- BLE 5.0 control via phone app or custom handset
- Optocoupler-isolated relay switching (ESP32 fully protected)
- Dedicated 18650 logic power with USB-C charging
- Separate 12.8V LiFePO4 switching battery with built-in BMS
- TVS diode protection on all output channels
- Status LED for BLE connectivity indication
- Professional Hammond 1455N1601BK black aluminum enclosure
- All modules socket-mounted — fully serviceable without soldering
- Panel DXF files included for Front Panel Express / laser cutting

---

## Quick Start

1. Order parts from [Bill of Materials](docs/02-bom.md)
2. Review the [Schematic](docs/03-schematic.md)
3. Build following the [Assembly Guide](docs/07-assembly.md)
4. Flash firmware from the [Firmware Guide](docs/06-firmware.md)
5. Drill panels using [Enclosure Guide](docs/05-enclosure.md) and DXF files in `/hardware`

---

## Repository Structure

```
remote-controller/
├── README.md
├── LICENSE
├── docs/
│   ├── 01-overview.md        System overview and design decisions
│   ├── 02-bom.md             Full bill of materials with links
│   ├── 03-schematic.md       Circuit schematic and wiring notes
│   ├── 04-pcb-layout.md      PCB layout guide (ElectroCookie)
│   ├── 05-enclosure.md       Hammond enclosure, drilling, panel labels
│   ├── 06-firmware.md        BLE firmware, flashing, app setup
│   └── 07-assembly.md        Step-by-step build order
├── hardware/
│   ├── front_panel.dxf       Front panel drill/engrave file
│   └── rear_panel.dxf        Rear panel drill/engrave file
└── firmware/
    └── remote_controller/
        └── remote_controller.ino
```

---

## License

Hardware and documentation: [CERN Open Hardware Licence v2 - Permissive (CERN-OHL-P)](LICENSE)

Firmware: [MIT License](LICENSE)

---

## Contributing

Issues and PRs welcome. If you build one, please share photos — open an issue tagged `build-log`.

---

## Acknowledgements

Designed with assistance from Claude (Anthropic). Schematic, BOM, DXF panel files, and firmware all generated and verified as part of this project.
