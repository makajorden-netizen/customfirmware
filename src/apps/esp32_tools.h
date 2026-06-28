#ifndef ESP32_TOOLS_H
#define ESP32_TOOLS_H

#include <furi.h>

/**
 * ESP32 Tools & Integration
 * GPIO communication with ESP32 devices
 */

typedef enum {
    ESP32ToolWiFiScanning,
    ESP32ToolBLEScanning,
    ESP32ToolPacketCapture,
    ESP32ToolFirmwareFlasher,
    ESP32ToolGPIOControl,
    ESP32ToolProgrammer,
    ESP32ToolCount,
} ESP32ToolType;

typedef struct {
    const char* name;
    const char* description;
    ESP32ToolType type;
    const char* version;
    bool requires_esp32_module;
    const char* gpio_pins; // Required GPIO pins
} ESP32Tool;

// ESP32 tools registry
const ESP32Tool esp32_tools[] = {
    {
        .name = "WiFi Scanner",
        .description = "Scan and analyze WiFi networks",
        .type = ESP32ToolWiFiScanning,
        .version = "2.5",
        .requires_esp32_module = true,
        .gpio_pins = "TX/RX + 5V/GND",
    },
    {
        .name = "BLE Scanner",
        .description = "Scan Bluetooth Low Energy devices",
        .type = ESP32ToolBLEScanning,
        .version = "2.2",
        .requires_esp32_module = true,
        .gpio_pins = "TX/RX + 5V/GND",
    },
    {
        .name = "Packet Capture",
        .description = "Capture network traffic via ESP32",
        .type = ESP32ToolPacketCapture,
        .version = "1.8",
        .requires_esp32_module = true,
        .gpio_pins = "TX/RX + 5V/GND",
    },
    {
        .name = "Firmware Flasher",
        .description = "Flash firmware to ESP32 via GPIO",
        .type = ESP32ToolFirmwareFlasher,
        .version = "2.0",
        .requires_esp32_module = true,
        .gpio_pins = "GPIO 0,2,13,14,15 + 5V/GND",
    },
    {
        .name = "GPIO Controller",
        .description = "Control GPIO pins on ESP32",
        .type = ESP32ToolGPIOControl,
        .version = "1.5",
        .requires_esp32_module = true,
        .gpio_pins = "GPIO 0-15 + 5V/GND",
    },
    {
        .name = "Programmer",
        .description = "Program ESP32 via UART",
        .type = ESP32ToolProgrammer,
        .version = "1.9",
        .requires_esp32_module = true,
        .gpio_pins = "TX/RX + 3.3V/GND",
    },
};

#define ESP32_TOOLS_COUNT (sizeof(esp32_tools) / sizeof(esp32_tools[0]))

// Tool launcher
void launch_esp32_tool(ESP32ToolType tool_type);

// Get tool by index
const ESP32Tool* get_esp32_tool(int index);

// Get tool by name
const ESP32Tool* find_esp32_tool_by_name(const char* name);

// Check ESP32 connection
bool check_esp32_connection(void);

#endif // ESP32_TOOLS_H