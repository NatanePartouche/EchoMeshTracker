#ifndef TECHOUTILS_H
#define TECHOUTILS_H

#include <Arduino.h>

class TEchoUtils {
public:
    // Power Management
    static float readBatteryVoltage();
    static bool isCharging();
    static int getBatteryPercentage();
    static void enterDeepSleep(uint32_t seconds = 0);
    
    // Display Utilities
    static void displayBootScreen();
    static void displayLowBattery();
    static void displayError(const String& error);
    
    // LoRa Utilities
    static String createStatusPacket();
    static String createLocationPacket(double lat, double lng, float alt = 0);
    static bool parseIncomingPacket(const String& packet);
    
    // System Utilities
    static String getDeviceID();
    static uint32_t getUptime();
    static int getFreeMemory();
    static void blinkLED(int times = 1, int delayMs = 200);
    
    // GPS Utilities
    static String formatCoordinate(double coord, bool isLatitude = true);
    static double calculateDistance(double lat1, double lng1, double lat2, double lng2);
    static String formatDistance(double meters);
    
private:
    static const int VBAT_PIN = 31;
    static const int CHARGE_PIN = 17;
    static const int LED_PIN = LED_BUILTIN;
};

#endif // TECHOUTILS_H 