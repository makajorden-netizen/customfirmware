#include "advanced_apps.h"
#include <stdlib.h>
#include <string.h>
#include <furi.h>

void launch_advanced_app(AdvancedAppType app_type) {
    const AdvancedApp* app = NULL;
    
    for(int i = 0; i < ADVANCED_APPS_COUNT; i++) {
        if(advanced_apps[i].type == app_type) {
            app = &advanced_apps[i];
            break;
        }
    }
    
    if(app == NULL) {
        furi_log_error("APP_LAUNCHER", "Advanced app not found: %d", app_type);
        return;
    }
    
    furi_log_info("APP_LAUNCHER", "Launching: %s v%s by %s", 
                  app->name, app->version, app->author);
    furi_log_info("APP_LAUNCHER", "Category: %s", app->category);
    
    // App-specific launch logic
    switch(app_type) {
        case AdvancedAppBLESpam:
            furi_log_info("BLE_SPAM", "BLE Spam started - Bluetooth notification attacks");
            furi_log_warn("BLE_SPAM", "For authorized testing only");
            break;
        case AdvancedAppESP32Marauder:
            furi_log_info("ESP32", "ESP32 Marauder started - WiFi & BLE scanning");
            furi_log_info("ESP32", "Ensure ESP32 module is connected to GPIO");
            break;
        case AdvancedAppWiFiWarDrive:
            furi_log_info("WARDRIVE", "WiFi War Drive started - Mapping networks");
            break;
        case AdvancedAppBTBeaconSpoof:
            furi_log_info("BT_BEACON", "BT Beacon Spoof started - Spoofing beacon signals");
            break;
        case AdvancedAppRFSignalAnalyzer:
            furi_log_info("RF_ANALYZER", "RF Signal Analyzer started");
            break;
        case AdvancedAppDeauther:
            furi_log_info("DEAUTH", "Deauther started - WiFi deauth tool");
            furi_log_warn("DEAUTH", "Use only on networks you own or have permission");
            break;
        case AdvancedAppPacketSniffer:
            furi_log_info("SNIFFER", "Packet Sniffer started - Capturing packets");
            break;
        default:
            furi_log_error("APP_LAUNCHER", "Unknown advanced app type");
            break;
    }
}

const AdvancedApp* get_advanced_app(int index) {
    if(index < 0 || index >= ADVANCED_APPS_COUNT) {
        return NULL;
    }
    return &advanced_apps[index];
}

const AdvancedApp* find_advanced_app_by_name(const char* name) {
    if(name == NULL) {
        return NULL;
    }
    
    for(int i = 0; i < ADVANCED_APPS_COUNT; i++) {
        if(strcmp(advanced_apps[i].name, name) == 0) {
            return &advanced_apps[i];
        }
    }
    return NULL;
}

const char* get_advanced_app_category(AdvancedAppType app_type) {
    for(int i = 0; i < ADVANCED_APPS_COUNT; i++) {
        if(advanced_apps[i].type == app_type) {
            return advanced_apps[i].category;
        }
    }
    return "Unknown";
}