# EchoMeshTracker

> Track. Monitor. Connect.


Firmware prêt à l’emploi pour le dispositif LilyGO T-Echo, intégrant un réseau maillé LoRa, un suivi GPS, un affichage e-paper et des capteurs environnementaux.

[![PlatformIO CI](https://img.shields.io/badge/PlatformIO-Ready-orange)](https://platformio.org/)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Hardware: T-Echo](https://img.shields.io/badge/Hardware-T--Echo-blue)](https://github.com/Xinyuan-LilyGO/T-Echo)

## Features

- **LoRa Mesh Networking** - Long-range communication (up to 10+ km)
- **GPS Tracking** - Real-time location with L76K GPS module
- **Environmental Monitoring** - Temperature, humidity, pressure (BME280)
- **E-Paper Display** - 4-page interface with system status
- **Power Management** - Battery monitoring and charging status
- **Auto Broadcasting** - Periodic status and location updates
- **Button Controls** - Navigate pages and send manual pings

## Hardware Requirements

- **LilyGO T-Echo** device
- **LoRa Antenna** (CRITICAL - never operate without antenna)
- **USB-C Cable** for programming
- **3.7V Li-Po Battery** (optional, for portable use)

## Quick Start

### 1. Clone and Build
```bash
git clone https://github.com/NatanePartouche/EchoMeshTracker.git
cd t-echo-lora-mesh
chmod +x build.sh
./build.sh
```

### 2. Flash Firmware
```bash
# Connect T-Echo via USB-C
# Double-tap reset button (enters bootloader mode)
pio run -t upload
```

### 3. Configure
- Device will boot and initialize all systems
- Use button to navigate between pages
- Double-click button to send ping messages

## Display Pages

1. **Main Status** - System overview, battery, connectivity
2. **GPS Data** - Location, altitude, satellite count
3. **Sensors** - Temperature, humidity, pressure
4. **System Info** - Uptime, memory, charging status

## Controls

- **Single Click**: Next page
- **Double Click**: Send LoRa ping
- **Reset Button**: Power cycle / enter bootloader (double-tap)

## LoRa Configuration

- **Frequency**: 915 MHz (US) - modify in `src/main.cpp` for other regions
- **Power**: 22 dBm (maximum)
- **Bandwidth**: 125 kHz
- **Spreading Factor**: 7
- **Coding Rate**: 4/5

## Development

### Project Structure
```
├── src/
│   └── main.cpp              # Main application
├── include/
│   └── pins.h               # Hardware pin definitions
├── lib/
│   └── TEchoUtils/          # Custom utility library
├── platformio.ini           # PlatformIO configuration
└── build.sh                # Build script
```

### Custom Library (TEchoUtils)
The project includes a custom utility library with:
- Power management functions
- Display utilities
- LoRa packet handling
- GPS coordinate formatting
- System diagnostics

### Adding Features
1. Modify `src/main.cpp` for main application logic
2. Add utilities to `lib/TEchoUtils/` for reusable functions
3. Update pin definitions in `include/pins.h` if needed

## Technical Specifications

| Component | Specification |
|-----------|---------------|
| MCU | nRF52840 (ARM Cortex-M4) |
| Display | 1.54" E-Paper (200x200) |
| Radio | SX1262 LoRa |
| GPS | L76K Module |
| Sensors | BME280 (Temp/Humidity/Pressure) |
| Battery | 3.7V Li-Po with USB-C charging |
| Connectivity | Bluetooth 5.0, USB-C |

## Power Consumption

| Mode | Current Draw |
|------|-------------|
| Active (backlight OFF) | ~42 mA |
| Active (backlight ON) | ~55 mA |
| Sleep Mode | ~0.25 mA |

## Troubleshooting

### Build Issues
- Ensure PlatformIO is installed: `pip install platformio`
- Check USB drivers for nRF52840
- Verify antenna connection before powering on

### Runtime Issues
- **No GPS fix**: Go outdoors, wait 5-10 minutes for cold start
- **LoRa not working**: Check antenna connection and frequency settings
- **Display blank**: Check SPI connections and power

### Factory Reset
Hold the program button while powering on to reset to defaults.

## Acknowledgments

- [LilyGO](https://github.com/Xinyuan-LilyGO/T-Echo) for the T-Echo hardware
- [Meshtastic](https://meshtastic.org/) for inspiration and mesh networking concepts
- [RadioLib](https://github.com/jgromes/RadioLib) for LoRa communication
- [PlatformIO](https://platformio.org/) for the development environment

## Safety & Legal

- **Always connect antenna before powering on** to prevent RF damage
- Use appropriate LoRa frequency for your region
- Follow local RF regulations and licensing requirements
- Battery safety: Don't short circuit or puncture Li-Po batteries

---

Made for the LoRa mesh community 
