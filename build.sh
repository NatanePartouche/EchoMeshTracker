#!/bin/bash

echo "🚀 Building T-Echo Meshtastic Project..."

# Check if PlatformIO is installed
if ! command -v pio &> /dev/null; then
    echo "❌ PlatformIO not found. Installing..."
    pip install platformio
fi

# Clean previous build
echo "🧹 Cleaning previous build..."
pio run -t clean

# Build the project
echo "🔨 Building firmware..."
pio run

if [ $? -eq 0 ]; then
    echo "✅ Build successful!"
    echo ""
    echo "📋 Next steps:"
    echo "1. Connect your T-Echo via USB-C"
    echo "2. Double-tap the reset button to enter bootloader mode"
    echo "3. Run: pio run -t upload"
    echo ""
    echo "Or flash manually:"
    echo "1. Device should appear as 'NRF52BOOT' drive"
    echo "2. Copy .pio/build/t-echo/firmware.uf2 to the drive"
    echo ""
    echo "🎯 Features included:"
    echo "- LoRa communication (915 MHz)"
    echo "- GPS tracking"
    echo "- BME280 environmental sensors"
    echo "- E-paper display with 4 pages"
    echo "- Button controls (click/double-click)"
    echo "- Battery monitoring"
    echo "- Automatic status broadcasting"
else
    echo "❌ Build failed!"
    exit 1
fi 