#include <Arduino.h>                     // Core Arduino functionality
#include <Wire.h>                        // I2C communication (used for sensors)
#include <SPI.h>                         // SPI communication (used for display and LoRa)
#include <RadioLib.h>                    // LoRa communication library
#include <TinyGPS++.h>                   // GPS data parsing library
#include <Adafruit_BME280.h>             // BME280 environmental sensor library
#include <GxEPD2_BW.h>                   // E-Ink display (black & white) driver
#include <GxEPD2_154_D67.h>              // Specific E-Ink model: 1.54" 200x200
#include <Button2.h>                     // Advanced button handling library
#include "pins.h"                        // Pin assignments (custom header file)

// Instantiate E-Ink display object
GxEPD2_BW<GxEPD2_154_D67, GxEPD2_154_D67::HEIGHT> display(GxEPD2_154_D67(EPD_CS, EPD_DC, EPD_RESET, EPD_BUSY));

// Instantiate LoRa radio object
SX1262 radio = new Module(LORA_CS, LORA_DIO1, LORA_RST, LORA_BUSY);

// Instantiate GPS parser
TinyGPSPlus gps;

// Instantiate BME280 sensor object
Adafruit_BME280 bme;

// Instantiate button object
Button2 button;

// Global state variables
bool loraInitialized = false;           // True if LoRa radio is successfully initialized
bool gpsEnabled = true;                 // True to enable GPS reading
bool sensorEnabled = false;             // True if BME280 sensor is available

// Time tracking variables (in milliseconds)
unsigned long lastTransmit = 0;         // Last time a LoRa message was sent
unsigned long lastGPSRead = 0;          // Last time GPS data was read
unsigned long lastSensorRead = 0;       // Last time sensor data was read
unsigned long lastDisplayUpdate = 0;    // Last time screen was updated

int currentPage = 0;                    // Index of the current screen page
const int totalPages = 4;               // Total number of display pages

// Structure to hold parsed GPS data
struct GPSData {
    double latitude = 0.0;
    double longitude = 0.0;
    double altitude = 0.0;
    int satellites = 0;
    bool valid = false;
} gpsData;

// Structure to hold sensor readings
struct SensorData {
    float temperature = 0.0;
    float humidity = 0.0;
    float pressure = 0.0;
    bool valid = false;
} sensorData;

// Structure to hold system-level info
struct SystemData {
    float batteryVoltage = 0.0;
    bool charging = false;
    unsigned long uptime = 0;
} systemData;

void setup() {
    Serial.begin(115200);                        // Start serial monitor
    delay(2000);                                 // Wait for components to power up

    Serial.println("T-Echo Meshtastic Demo Starting...");

    // Configure hardware pins
    pinMode(LED_PIN, OUTPUT);
    pinMode(VBAT_PIN, INPUT);                   // Battery voltage pin
    pinMode(CHARGE_PIN, INPUT_PULLUP);          // Charger status pin
    pinMode(GPS_WAKEUP_PIN, OUTPUT);            // Wake-up control for GPS module
    digitalWrite(GPS_WAKEUP_PIN, HIGH);         // Keep GPS awake

    // Start I2C communication
    Wire.begin(I2C_SDA, I2C_SCL);

    // Initialize BME280 sensor (if available)
    if (bme.begin(0x76)) {
        sensorEnabled = true;
        Serial.println("BME280 sensor initialized");
    } else {
        Serial.println("BME280 sensor not found");
    }

    // Initialize GPS UART communication
    Serial1.begin(9600, SERIAL_8N1, GPS_RX_PIN, GPS_TX_PIN);
    Serial.println("GPS initialized");

    // Initialize E-Ink display
    display.init(115200);
    display.setRotation(1);                     // Landscape mode
    display.setTextColor(GxEPD_BLACK);          // Set text color
    display.setFont();                          // Use default font
    Serial.println("Display initialized");

    // Initialize LoRa radio at 915 MHz (US frequency)
    Serial.print("Initializing LoRa... ");
    int state = radio.begin(915.0);
    if (state == RADIOLIB_ERR_NONE) {
        loraInitialized = true;
        radio.setOutputPower(22);              // Max output power
        radio.setCurrentLimit(80);             // Limit current draw (mA)
        radio.setBandwidth(125.0);             // Bandwidth in kHz
        radio.setSpreadingFactor(7);           // Spread factor (7–12)
        radio.setCodingRate(5);                // Coding rate (4/5)
        Serial.println("success!");
    } else {
        Serial.print("failed, code ");
        Serial.println(state);
    }

    // Configure button behavior
    button.begin(BUTTON_PIN);
    button.setClickHandler([](Button2& btn) {
        currentPage = (currentPage + 1) % totalPages;  // Cycle through pages
        Serial.printf("Switched to page %d\n", currentPage);
    });
    button.setDoubleClickHandler([](Button2& btn) {
        if (loraInitialized) {
            sendPing();                                // Send ping message
        }
    });

    updateDisplay();                            // Display initial page

    Serial.println("Setup complete!");
    digitalWrite(LED_PIN, HIGH);                // Blink LED to indicate ready
    delay(500);
    digitalWrite(LED_PIN, LOW);
}

void loop() {
    unsigned long now = millis();               // Get time since startup

    button.loop();                              // Check button state

    // Periodically read GPS data
    if (gpsEnabled && now - lastGPSRead > 1000) {
        readGPS();
        lastGPSRead = now;
    }

    // Periodically read sensor data
    if (sensorEnabled && now - lastSensorRead > 5000) {
        readSensors();
        lastSensorRead = now;
    }

    updateSystemData();                         // Refresh battery and uptime info

    // Refresh display every 10 seconds
    if (now - lastDisplayUpdate > 10000) {
        updateDisplay();
        lastDisplayUpdate = now;
    }

    // Send LoRa message every 30 seconds
    if (loraInitialized && now - lastTransmit > 30000) {
        sendStatusMessage();
        lastTransmit = now;
    }

    // Check for incoming LoRa messages
    if (loraInitialized) {
        checkLoRaMessages();
    }

    delay(100);                                 // Reduce CPU usage
}

void readGPS() {
    // Read and parse GPS data from Serial1
    while (Serial1.available() > 0) {
        if (gps.encode(Serial1.read())) {
            if (gps.location.isValid()) {
                gpsData.latitude = gps.location.lat();
                gpsData.longitude = gps.location.lng();
                gpsData.altitude = gps.altitude.meters();
                gpsData.satellites = gps.satellites.value();
                gpsData.valid = true;
            }
        }
    }
}

void readSensors() {
    // Read temperature, humidity and pressure from BME280
    if (sensorEnabled) {
        sensorData.temperature = bme.readTemperature();
        sensorData.humidity = bme.readHumidity();
        sensorData.pressure = bme.readPressure() / 100.0F; // Convert Pa to hPa
        sensorData.valid = true;
    }
}

void updateSystemData() {
    int adcValue = analogRead(VBAT_PIN);                            // Read battery voltage
    systemData.batteryVoltage = (adcValue * 3.3 * 2.0) / 1024.0;    // Calculate voltage (voltage divider)
    systemData.charging = !digitalRead(CHARGE_PIN);                // LOW means charging
    systemData.uptime = millis() / 1000;                           // Convert uptime to seconds
}

void updateDisplay() {
    display.fillScreen(GxEPD_WHITE);            // Clear screen
    display.setCursor(0, 0);                    // Top-left corner

    // Display one of four pages
    switch (currentPage) {
        case 0: displayMainPage(); break;
        case 1: displayGPSPage(); break;
        case 2: displaySensorPage(); break;
        case 3: displaySystemPage(); break;
    }

    display.display();                          // Commit content to screen
}

void displayMainPage() {
    display.setTextSize(2);
    display.println("T-Echo Mesh");
    display.setTextSize(1);
    display.println();
    display.printf("LoRa: %s\n", loraInitialized ? "OK" : "FAIL");
    display.printf("GPS: %s\n", gpsData.valid ? "LOCK" : "SEARCH");
    display.printf("Sensor: %s\n", sensorEnabled ? "OK" : "N/A");
    display.println();
    display.printf("Battery: %.2fV %s\n", systemData.batteryVoltage, systemData.charging ? "CHG" : "");
    display.printf("Uptime: %lus\n", systemData.uptime);
    display.println();
    display.println("Click: Next Page");
    display.println("Double: Send Ping");
}

void displayGPSPage() {
    display.setTextSize(2);
    display.println("GPS Data");
    display.setTextSize(1);
    display.println();
    if (gpsData.valid) {
        display.printf("Lat: %.6f\n", gpsData.latitude);
        display.printf("Lng: %.6f\n", gpsData.longitude);
        display.printf("Alt: %.1fm\n", gpsData.altitude);
        display.printf("Sats: %d\n", gpsData.satellites);
    } else {
        display.println("Searching for");
        display.println("satellites...");
        display.println();
        display.println("Go outside for");
        display.println("better signal");
    }
}

void displaySensorPage() {
    display.setTextSize(2);
    display.println("Sensors");
    display.setTextSize(1);
    display.println();
    if (sensorEnabled && sensorData.valid) {
        display.printf("Temp: %.1f C\n", sensorData.temperature);
        display.printf("Humidity: %.1f%%\n", sensorData.humidity);
        display.printf("Pressure: %.1f hPa\n", sensorData.pressure);
    } else {
        display.println("BME280 sensor");
        display.println("not available");
    }
}

void displaySystemPage() {
    display.setTextSize(2);
    display.println("System");
    display.setTextSize(1);
    display.println();
    display.printf("Battery: %.2fV\n", systemData.batteryVoltage);
    display.printf("Charging: %s\n", systemData.charging ? "Yes" : "No");
    display.printf("Uptime: %lu s\n", systemData.uptime);
}

void sendPing() {
    if (!loraInitialized) return;
    String message = "PING from T-Echo";
    Serial.println("Sending ping...");
    int state = radio.transmit(message);
    if (state == RADIOLIB_ERR_NONE) {
        Serial.println("Ping sent successfully!");
        digitalWrite(LED_PIN, HIGH);
        delay(100);
        digitalWrite(LED_PIN, LOW);
    } else {
        Serial.printf("Ping failed, code %d\n", state);
    }
}

void sendStatusMessage() {
    if (!loraInitialized) return;
    String message = "STATUS:";
    message += "BAT=" + String(systemData.batteryVoltage, 2) + "V,";
    if (gpsData.valid) {
        message += "GPS=" + String(gpsData.latitude, 6) + "," + String(gpsData.longitude, 6) + ",";
    }
    if (sensorEnabled && sensorData.valid) {
        message += "TEMP=" + String(sensorData.temperature, 1) + "C,";
        message += "HUM=" + String(sensorData.humidity, 1) + "%";
    }
    Serial.println("Sending status: " + message);
    int state = radio.transmit(message);
    if (state == RADIOLIB_ERR_NONE) {
        Serial.println("Status sent successfully!");
    } else {
        Serial.printf("Status send failed, code %d\n", state);
    }
}

void checkLoRaMessages() {
    String message;
    int state = radio.receive(message);
    if (state == RADIOLIB_ERR_NONE) {
        Serial.println("Received: " + message);
        Serial.printf("RSSI: %.2f dBm\n", radio.getRSSI());
        Serial.printf("SNR: %.2f dB\n", radio.getSNR());
        for (int i = 0; i < 3; i++) {
            digitalWrite(LED_PIN, HIGH);
            delay(100);
            digitalWrite(LED_PIN, LOW);
            delay(100);
        }
    }
}

// Returns the amount of free RAM (in bytes)
extern "C" char* sbrk(int incr);
int freeMemory() {
    char top;
    return &top - reinterpret_cast<char*>(sbrk(0));
}