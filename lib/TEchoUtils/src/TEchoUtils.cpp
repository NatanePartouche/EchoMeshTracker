#include "TEchoUtils.h"
#include <math.h>

// Power Management Functions
float TEchoUtils::readBatteryVoltage() {
    int adcValue = analogRead(VBAT_PIN);
    return (adcValue * 3.3 * 2.0) / 1024.0; // Voltage divider calculation
}

bool TEchoUtils::isCharging() {
    return !digitalRead(CHARGE_PIN); // Active low
}

int TEchoUtils::getBatteryPercentage() {
    float voltage = readBatteryVoltage();
    // Li-Po voltage range: 3.0V (0%) to 4.2V (100%)
    if (voltage >= 4.2) return 100;
    if (voltage <= 3.0) return 0;
    return (int)((voltage - 3.0) / 1.2 * 100);
}

void TEchoUtils::enterDeepSleep(uint32_t seconds) {
    // Implementation depends on nRF52 sleep functions
    // This is a placeholder - actual implementation would use nRF52 SDK
    Serial.println("Entering deep sleep...");
    delay(1000);
}

// System Utilities
String TEchoUtils::getDeviceID() {
    // Generate a unique ID based on MAC address or chip ID
    uint32_t chipId = 0;
    // This would typically read from nRF52 device ID registers
    return "TECHO_" + String(chipId, HEX);
}

uint32_t TEchoUtils::getUptime() {
    return millis() / 1000;
}

int TEchoUtils::getFreeMemory() {
    // Simple free memory calculation
    extern char _end;
    extern "C" char* sbrk(int incr);
    char* heapEnd = sbrk(0);
    return (char*)&_end - heapEnd;
}

void TEchoUtils::blinkLED(int times, int delayMs) {
    for (int i = 0; i < times; i++) {
        digitalWrite(LED_PIN, HIGH);
        delay(delayMs);
        digitalWrite(LED_PIN, LOW);
        if (i < times - 1) delay(delayMs);
    }
}

// LoRa Utilities
String TEchoUtils::createStatusPacket() {
    String packet = "STATUS|";
    packet += "BAT:" + String(readBatteryVoltage(), 2) + "V|";
    packet += "CHG:" + String(isCharging() ? "1" : "0") + "|";
    packet += "UP:" + String(getUptime()) + "s|";
    packet += "ID:" + getDeviceID();
    return packet;
}

String TEchoUtils::createLocationPacket(double lat, double lng, float alt) {
    String packet = "GPS|";
    packet += "LAT:" + String(lat, 6) + "|";
    packet += "LNG:" + String(lng, 6) + "|";
    packet += "ALT:" + String(alt, 1) + "m|";
    packet += "ID:" + getDeviceID();
    return packet;
}

bool TEchoUtils::parseIncomingPacket(const String& packet) {
    // Simple packet parser - returns true if packet is valid
    if (packet.length() < 5) return false;
    if (packet.indexOf("|") == -1) return false;
    
    Serial.println("Parsed packet: " + packet);
    return true;
}

// GPS Utilities
String TEchoUtils::formatCoordinate(double coord, bool isLatitude) {
    char direction = ' ';
    if (isLatitude) {
        direction = (coord >= 0) ? 'N' : 'S';
    } else {
        direction = (coord >= 0) ? 'E' : 'W';
    }
    
    coord = abs(coord);
    int degrees = (int)coord;
    double minutes = (coord - degrees) * 60.0;
    
    return String(degrees) + "°" + String(minutes, 4) + "'" + direction;
}

double TEchoUtils::calculateDistance(double lat1, double lng1, double lat2, double lng2) {
    // Haversine formula for calculating distance between two GPS coordinates
    const double R = 6371000; // Earth's radius in meters
    
    double dLat = (lat2 - lat1) * PI / 180.0;
    double dLng = (lng2 - lng1) * PI / 180.0;
    
    double a = sin(dLat/2) * sin(dLat/2) +
               cos(lat1 * PI / 180.0) * cos(lat2 * PI / 180.0) *
               sin(dLng/2) * sin(dLng/2);
    
    double c = 2 * atan2(sqrt(a), sqrt(1-a));
    return R * c;
}

String TEchoUtils::formatDistance(double meters) {
    if (meters < 1000) {
        return String((int)meters) + "m";
    } else if (meters < 10000) {
        return String(meters/1000.0, 1) + "km";
    } else {
        return String((int)(meters/1000)) + "km";
    }
} 