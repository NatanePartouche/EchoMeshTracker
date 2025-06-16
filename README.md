# RadioMeshTracker

> **Track. Communicate. Monitor. Anywhere.**

Firmware for **LilyGO T-Echo**, integrating **LoRa mesh networking**, **GPS tracking**, **e-paper display**, and **environmental sensing** — ideal for off-grid communication and monitoring.

---

### 🎯 Project Overview

**RadioMeshTracker** is a compact, autonomous device that enables:
- 📡 Long-range (10+ km) **LoRa Mesh communication**
- 📍 Real-time **GPS tracking**
- 🌡️ Displaying live **environmental data** (temperature, humidity, pressure)
- 🔋 Operating off-grid on battery with **efficient power management**

It is built for low-power, off-network deployments where tracking, monitoring, and messaging are critical — all without relying on mobile or internet infrastructure.

---

### 🧭 Use Cases

- 🥾 Tracking individuals in **remote or signal-dead zones**
- 🪖 Tactical or humanitarian **LoRa Mesh communications**
- 🌍 **Environmental sensing** for research or distributed IoT
- 🛰️ Deploying a **mesh of autonomous sensor nodes**

---

## ✨ Features

- 📡 **LoRa Mesh** – Peer-to-peer long-range radio communication (10+ km)
- 📍 **GPS Tracking** – Real-time position updates via L76K GPS
- 🌡️ **Environmental Sensing** – Temperature, humidity & pressure (BME280)
- 🖥️ **E-Paper Display** – Low-power 4-page interface
- 🔋 **Power Monitoring** – Battery level, USB charging
- 📤 **Auto Ping** – Periodic broadcast of location and status
- 🔘 **Button Navigation** – Page control and manual ping

---

## 🛠️ Required Hardware

- ✅ **LilyGO T-Echo** board
- 📡 **LoRa Antenna** (Required for operation!)
- 🔌 **USB-C Cable**
- 🔋 **3.7V Li-Po Battery** (Optional, for portable use)

---

## 🚀 Quick Start

```bash
git clone https://github.com/NatanePartouche/RadioMeshTracker.git
cd RadioMeshTracker
chmod +x build.sh
./build.sh
```

### Upload the Firmware

```bash
pio run -t upload
```

- Connect T-Echo via USB-C
- Press reset twice to enter bootloader mode (LED will blink)

---

## 📄 Display Interface

1. 🟢 **Main Page** – Battery %, mesh link, system status
2. 📡 **GPS Page** – Latitude, longitude, altitude, satellite count
3. 🌡️ **Sensors Page** – Temperature (°C), humidity (%), pressure (hPa)
4. ⚙️ **System Page** – Uptime, memory usage, charging state

---

## 🎮 Device Controls

| Action          | Result                      |
|-----------------|-----------------------------|
| 🔘 Single Click | Switch to next page         |
| 🔘 Double Click | Send immediate LoRa ping    |
| 🔁 Hold RESET   | Reboot / enter bootloader   |

---

## 📶 LoRa Configuration

| Parameter        | Value     |
|------------------|-----------|
| Frequency        | 915 MHz   |
| TX Power         | 22 dBm    |
| Bandwidth        | 125 kHz   |
| Spreading Factor | SF7       |
| Coding Rate      | 4/5       |

⚙️ You can modify these settings in `src/main.cpp` to match your region or use case.

---

## 📁 Project Structure

```
├── src/              # Core firmware logic
├── include/          # Pin mappings and constants
├── lib/TEchoUtils/   # LoRa, GPS, display, and utility drivers
├── build.sh          # Linux/macOS build helper
└── platformio.ini    # PlatformIO configuration
```

---

## 📐 Technical Specifications

| Component    | Specs                          |
|--------------|--------------------------------|
| MCU          | nRF52840 (ARM Cortex-M4)       |
| Display      | 1.54” E-Ink (200x200 pixels)   |
| LoRa Radio   | SX1262                         |
| GPS Module   | Quectel L76K                   |
| Sensor       | BME280 (Temp / Hum / Pressure) |
| Battery      | 3.7V Li-Po + USB-C charging    |
| Wireless     | Bluetooth 5.0 compatible       |

---

## 🔋 Power Consumption

| Mode         | Current Draw |
|--------------|---------------|
| Active Mode  | ~42 mA        |
| Display      | ~55 mA        |
| Sleep Mode   | ~0.25 mA      |

💡 E-paper display consumes power only during refresh, perfect for low-power outdoor use.

---

## 🧪 Troubleshooting

- ⚠️ **No GPS signal?** Go outside, allow 5–10 minutes to get a fix.
- ⚠️ **LoRa not working?** Make sure the antenna is attached and the frequency matches your region.
- ⚠️ **Blank screen?** Check power supply and SPI connections.
- 🔁 **Reset fails?** Hold the PROGRAM button while connecting USB.

---

## 🙏 Credits

- LilyGO – T-Echo board
- Meshtastic – Inspiration for LoRa mesh
- RadioLib – LoRa/GPS library
- PlatformIO – Embedded development made easy

---

## ⚖️ Legal & Safety Notes

- 🔥 Always connect the LoRa antenna before powering the board
- 📡 Ensure you're using LoRa frequencies allowed in your region
- ⚠️ Li-Po batteries can be dangerous—charge and handle with care

---

Made with ❤️ for open-source mesh explorers.

🔗 [Download Latest Release](https://github.com/NatanePartouche/RadioMeshTracker/releases/latest)