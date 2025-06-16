
# EchoMeshTracker

> **Track. Monitor. Connect.**

Firmware for **LilyGO T-Echo** featuring **LoRa mesh**, **GPS tracking**, **e-paper display**, and **environmental sensors**.

[![PlatformIO CI](https://img.shields.io/badge/PlatformIO-Ready-orange)](https://platformio.org/)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Hardware: T-Echo](https://img.shields.io/badge/Hardware-T--Echo-blue)](https://github.com/Xinyuan-LilyGO/T-Echo)

---

## ✨ Features

- 📡 **LoRa Mesh** – Long-range communication (10+ km)
- 📍 **GPS Tracking** – Real-time location via L76K module
- 🌡️ **Environmental Sensors** – Temp, humidity, pressure (BME280)
- 🖥️ **E-Paper Display** – 4 pages of system info
- 🔋 **Power Management** – Battery status and charging
- 📤 **Auto Broadcast** – Periodic status & location pings
- 🔘 **Button Control** – Page nav & manual pings

---

## 🛠️ Hardware

- LilyGO **T-Echo**
- 🧲 **LoRa Antenna** (⚠️ Required!)
- 🔌 **USB-C Cable**
- 🔋 **3.7V Li-Po Battery** (optional)

---

## 🚀 Quick Start

```bash
git clone https://github.com/NatanePartouche/EchoMeshTracker.git
cd EchoMeshTracker
chmod +x build.sh
./build.sh
```

### Flash Firmware
```bash
pio run -t upload
```

- Connect T-Echo via USB-C
- Double-tap reset to enter bootloader

---

## 📄 Display Pages

1. 🟢 **Main** – Battery, mesh, system state
2. 📡 **GPS** – Coordinates, altitude, satellites
3. 🌡️ **Sensors** – Temp, humidity, pressure
4. ⚙️ **System** – Uptime, memory, charging

---

## 🎮 Controls

- 🔘 *Click*: Next page
- 🔘 *Double-click*: Send LoRa ping
- 🔁 *Reset*: Reboot / bootloader mode

---

## 📶 LoRa Settings

| Setting         | Value         |
|----------------|---------------|
| Frequency       | 915 MHz       |
| TX Power        | 22 dBm        |
| Bandwidth       | 125 kHz       |
| Spreading Factor| 7             |
| Coding Rate     | 4/5           |

Edit these in `src/main.cpp` as needed.

---

## 📁 Project Structure

```
├── src/            # Main logic
├── include/        # Pin mappings
├── lib/TEchoUtils/ # Utilities (LoRa, GPS, Display)
├── build.sh        # Build helper
└── platformio.ini  # Project config
```

---

## 📐 Technical Specs

| Component | Details               |
|-----------|-----------------------|
| MCU       | nRF52840 (ARM M4)     |
| Display   | 1.54" E-Paper (200x200) |
| Radio     | SX1262 LoRa           |
| GPS       | L76K module           |
| Sensor    | BME280 (Temp/Hum/Pres)|
| Battery   | Li-Po 3.7V + USB-C    |
| Connectivity | Bluetooth 5.0      |

---

## 🔋 Power Usage

| Mode        | Draw     |
|-------------|----------|
| Active      | ~42 mA   |
| Backlight   | ~55 mA   |
| Sleep       | ~0.25 mA |

---

## 🧪 Troubleshooting

- ⚠️ **No GPS**: Try outdoors, wait 5–10 min
- ⚠️ **LoRa issue**: Check antenna & region
- ⚠️ **Blank display**: Check SPI & power

Reset: Hold PROGRAM button during power-on.

---

## 🙏 Credits

- [LilyGO](https://github.com/Xinyuan-LilyGO/T-Echo)
- [Meshtastic](https://meshtastic.org/)
- [RadioLib](https://github.com/jgromes/RadioLib)
- [PlatformIO](https://platformio.org/)

---

## ⚖️ Safety & Legal

- 🔥 Always connect antenna before power
- 📡 Use correct LoRa frequencies for your region
- ⚠️ Handle Li-Po batteries with care

---

Made for the LoRa mesh community ❤️

🔗 [GitHub Repo](https://github.com/NatanePartouche/EchoMeshTracker.git)
