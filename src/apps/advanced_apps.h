#ifndef ADVANCED_APPS_H
#define ADVANCED_APPS_H

#include <furi.h>

/**
 * Advanced & Hacking Tools Apps
 * Bluetooth, WiFi, and RF tools for Flipper Zero
 */

typedef enum {
    AdvancedAppBLESpam,
    AdvancedAppESP32Marauder,
    AdvancedAppWiFiWarDrive,
    AdvancedAppBTBeaconSpoof,
    AdvancedAppRFSignalAnalyzer,
    AdvancedAppDeauther,
    AdvancedAppPacketSniffer,
    AdvancedAppCount,
} AdvancedAppType;

typedef struct {
    const char* name;
    const char* description;
    AdvancedAppType type;
    const char* author;
    const char* version;
    const char* category; // "Bluetooth", "WiFi", "RF", "ESP32"
} AdvancedApp;

// Advanced apps registry
const AdvancedApp advanced_apps[] = {
    {
        .name = "BLE Spam",
        .description = "Bluetooth spam & notification attacks",
        .type = AdvancedAppBLESpam,
        .author = "Community",
        .version = "2.3",
        .category = "Bluetooth",
    },
    {
        .name = "ESP32 Marauder",
        .description = "WiFi & BLE scanning with ESP32",
        .type = AdvancedAppESP32Marauder,
        .author = "justcallmekoko",
        .version = "3.1",
        .category = "ESP32",
    },
    {
        .name = "WiFi War Drive",
        .description = "Map WiFi networks (requires GPS)",
        .type = AdvancedAppWiFiWarDrive,
        .author = "Community",
        .version = "1.8",
        .category = "WiFi",
    },
    {
        .name = "BT Beacon Spoof",
        .description = "Spoof Bluetooth beacon signals",
        .type = AdvancedAppBTBeaconSpoof,
        .author = "Community",
        .version = "1.5",
        .category = "Bluetooth",
    },
    {
        .name = "RF Signal Analyzer",
        .description = "Advanced RF signal analysis",
        .type = AdvancedAppRFSignalAnalyzer,
        .author = "Community",
        .version = "2.0",
        .category = "RF",
    },
    {
        .name = "Deauther",
        .description = "WiFi deauthentication attack tool",
        .type = AdvancedAppDeauther,
        .author = "Community",
        .version = "2.4",
        .category = "WiFi",
    },
    {
        .name = "Packet Sniffer",
        .description = "Capture and analyze network packets",
        .type = AdvancedAppPacketSniffer,
        .author = "Community",
        .version = "1.9",
        .category = "WiFi",
    },
};

#define ADVANCED_APPS_COUNT (sizeof(advanced_apps) / sizeof(advanced_apps[0]))

// App launcher function
void launch_advanced_app(AdvancedAppType app_type);

// Get app by index
const AdvancedApp* get_advanced_app(int index);

// Get app by name
const AdvancedApp* find_advanced_app_by_name(const char* name);

// Get app category
const char* get_advanced_app_category(AdvancedAppType app_type);

#endif // ADVANCED_APPS_H