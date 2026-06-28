#include "nrf24_tools.h"
#include <stdlib.h>
#include <string.h>
#include <furi.h>

static uint8_t current_channel = 76; // Default channel

void launch_nrf24_tool(NRF24ToolType tool_type) {
    const NRF24Tool* tool = NULL;
    
    for(int i = 0; i < NRF24_TOOLS_COUNT; i++) {
        if(nrf24_tools[i].type == tool_type) {
            tool = &nrf24_tools[i];
            break;
        }
    }
    
    if(tool == NULL) {
        furi_log_error("NRF24_LAUNCHER", "Tool not found: %d", tool_type);
        return;
    }
    
    furi_log_info("NRF24_LAUNCHER", "Launching: %s v%s", tool->name, tool->version);
    furi_log_info("NRF24_LAUNCHER", "Frequency: %s", tool->frequency);
    furi_log_info("NRF24_LAUNCHER", "Current Channel: %d", current_channel);
    
    if(tool->requires_nrf24_module) {
        furi_log_info("NRF24_LAUNCHER", "NRF24 module required");
        furi_log_info("NRF24_LAUNCHER", "GPIO pins: %s", tool->gpio_pins);
    }
    
    // Tool-specific launch logic
    switch(tool_type) {
        case NRF24ToolChannelScanner:
            furi_log_info("NRF24_SCANNER", "Channel Scanner started");
            furi_log_info("NRF24_SCANNER", "Scanning 2.4GHz channels for activity");
            break;
        case NRF24ToolPacketSniffer:
            furi_log_info("NRF24_SNIFFER", "Packet Sniffer started");
            furi_log_info("NRF24_SNIFFER", "Passively monitoring NRF24 traffic");
            break;
        case NRF24ToolMouseJacker:
            furi_log_warn("NRF24_MOUSEJACK", "MouseJacker started - For authorized testing only!");
            furi_log_info("NRF24_MOUSEJACK", "Scanning for wireless mice on Unifying receivers");
            break;
        case NRF24ToolKeyboardJacker:
            furi_log_warn("NRF24_KEYJACK", "Keyboard Jacker started - For authorized testing only!");
            furi_log_info("NRF24_KEYJACK", "Monitoring wireless keyboard communications");
            break;
        case NRF24ToolJammer:
            furi_log_warn("NRF24_JAMMER", "Jammer started - USE ONLY IN RF-SHIELDED ENVIRONMENT!");
            furi_log_error("NRF24_JAMMER", "ILLEGAL OUTSIDE OF CONTROLLED TESTING");
            break;
        case NRF24ToolPayloadTransmitter:
            furi_log_info("NRF24_TX", "Payload Transmitter started");
            furi_log_info("NRF24_TX", "Ready to craft and transmit payloads");
            break;
        case NRF24ToolAddressScanner:
            furi_log_info("NRF24_ADDR", "Address Scanner started");
            furi_log_info("NRF24_ADDR", "Discovering NRF24 device addresses");
            break;
        default:
            furi_log_error("NRF24_LAUNCHER", "Unknown tool type");
            break;
    }
}

const NRF24Tool* get_nrf24_tool(int index) {
    if(index < 0 || index >= NRF24_TOOLS_COUNT) {
        return NULL;
    }
    return &nrf24_tools[index];
}

const NRF24Tool* find_nrf24_tool_by_name(const char* name) {
    if(name == NULL) {
        return NULL;
    }
    
    for(int i = 0; i < NRF24_TOOLS_COUNT; i++) {
        if(strcmp(nrf24_tools[i].name, name) == 0) {
            return &nrf24_tools[i];
        }
    }
    return NULL;
}

bool check_nrf24_connection(void) {
    // TODO: Implement actual GPIO connection check
    furi_log_info("NRF24_CHECK", "Checking NRF24 connection via GPIO...");
    furi_log_info("NRF24_CHECK", "CE pin (GPIO14), CSN pin (GPIO7), SPI lines...");
    return true; // Placeholder
}

void nrf24_set_channel(uint8_t channel) {
    if(channel > 125) {
        furi_log_error("NRF24", "Invalid channel %d (0-125)", channel);
        return;
    }
    current_channel = channel;
    furi_log_info("NRF24", "Channel set to: %d (%.2f GHz)", channel, 2.4f + (channel * 0.001f));
}

uint8_t nrf24_get_channel(void) {
    return current_channel;
}