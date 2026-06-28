#include "esp32_tools.h"
#include <stdlib.h>
#include <string.h>
#include <furi.h>

void launch_esp32_tool(ESP32ToolType tool_type) {
    const ESP32Tool* tool = NULL;
    
    for(int i = 0; i < ESP32_TOOLS_COUNT; i++) {
        if(esp32_tools[i].type == tool_type) {
            tool = &esp32_tools[i];
            break;
        }
    }
    
    if(tool == NULL) {
        furi_log_error("ESP32_LAUNCHER", "Tool not found: %d", tool_type);
        return;
    }
    
    furi_log_info("ESP32_LAUNCHER", "Launching: %s v%s", tool->name, tool->version);
    
    if(tool->requires_esp32_module) {
        furi_log_info("ESP32_LAUNCHER", "ESP32 module required");
        furi_log_info("ESP32_LAUNCHER", "GPIO pins: %s", tool->gpio_pins);
    }
    
    // Tool-specific launch logic
    switch(tool_type) {
        case ESP32ToolWiFiScanning:
            furi_log_info("ESP32_WIFI", "WiFi Scanner started");
            break;
        case ESP32ToolBLEScanning:
            furi_log_info("ESP32_BLE", "BLE Scanner started");
            break;
        case ESP32ToolPacketCapture:
            furi_log_info("ESP32_CAPTURE", "Packet Capture started");
            break;
        case ESP32ToolFirmwareFlasher:
            furi_log_info("ESP32_FLASH", "Firmware Flasher started");
            break;
        case ESP32ToolGPIOControl:
            furi_log_info("ESP32_GPIO", "GPIO Controller started");
            break;
        case ESP32ToolProgrammer:
            furi_log_info("ESP32_PROG", "Programmer started");
            break;
        default:
            furi_log_error("ESP32_LAUNCHER", "Unknown tool type");
            break;
    }
}

const ESP32Tool* get_esp32_tool(int index) {
    if(index < 0 || index >= ESP32_TOOLS_COUNT) {
        return NULL;
    }
    return &esp32_tools[index];
}

const ESP32Tool* find_esp32_tool_by_name(const char* name) {
    if(name == NULL) {
        return NULL;
    }
    
    for(int i = 0; i < ESP32_TOOLS_COUNT; i++) {
        if(strcmp(esp32_tools[i].name, name) == 0) {
            return &esp32_tools[i];
        }
    }
    return NULL;
}

bool check_esp32_connection(void) {
    // TODO: Implement actual GPIO connection check
    furi_log_info("ESP32_CHECK", "Checking ESP32 connection via GPIO...");
    return true; // Placeholder
}