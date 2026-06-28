#ifndef NRF24_TOOLS_H
#define NRF24_TOOLS_H

#include <furi.h>

/**
 * NRF24 Tools & Integration
 * 2.4GHz wireless module tools for Flipper Zero
 */

typedef enum {
    NRF24ToolChannelScanner,
    NRF24ToolPacketSniffer,
    NRF24ToolMouseJacker,
    NRF24ToolKeyboardJacker,
    NRF24ToolJammer,
    NRF24ToolPayloadTransmitter,
    NRF24ToolAddressScanner,
    NRF24ToolCount,
} NRF24ToolType;

typedef struct {
    const char* name;
    const char* description;
    NRF24ToolType type;
    const char* version;
    bool requires_nrf24_module;
    const char* gpio_pins; // Required GPIO pins
    const char* frequency;  // Operating frequency
} NRF24Tool;

// NRF24 tools registry
const NRF24Tool nrf24_tools[] = {
    {
        .name = "Channel Scanner",
        .description = "Scan 2.4GHz channels for activity",
        .type = NRF24ToolChannelScanner,
        .version = "2.1",
        .requires_nrf24_module = true,
        .gpio_pins = "CE(GPIO14), CSN(GPIO7), CLK, MOSI, MISO",
        .frequency = "2.4GHz ISM",
    },
    {
        .name = "Packet Sniffer",
        .description = "Passively sniff NRF24 packets",
        .type = NRF24ToolPacketSniffer,
        .version = "2.3",
        .requires_nrf24_module = true,
        .gpio_pins = "CE(GPIO14), CSN(GPIO7), CLK, MOSI, MISO",
        .frequency = "2.4GHz ISM",
    },
    {
        .name = "MouseJacker",
        .description = "Exploit wireless mice/keyboards (HID)",
        .type = NRF24ToolMouseJacker,
        .version = "1.8",
        .requires_nrf24_module = true,
        .gpio_pins = "CE(GPIO14), CSN(GPIO7), CLK, MOSI, MISO",
        .frequency = "2.4GHz ISM",
    },
    {
        .name = "Keyboard Jacker",
        .description = "Intercept keyboard transmissions",
        .type = NRF24ToolKeyboardJacker,
        .version = "1.6",
        .requires_nrf24_module = true,
        .gpio_pins = "CE(GPIO14), CSN(GPIO7), CLK, MOSI, MISO",
        .frequency = "2.4GHz ISM",
    },
    {
        .name = "Jammer",
        .description = "2.4GHz spectrum jammer (for testing)",
        .type = NRF24ToolJammer,
        .version = "1.9",
        .requires_nrf24_module = true,
        .gpio_pins = "CE(GPIO14), CSN(GPIO7), CLK, MOSI, MISO",
        .frequency = "2.4GHz ISM",
    },
    {
        .name = "Payload Transmitter",
        .description = "Create and transmit custom NRF24 payloads",
        .type = NRF24ToolPayloadTransmitter,
        .version = "2.0",
        .requires_nrf24_module = true,
        .gpio_pins = "CE(GPIO14), CSN(GPIO7), CLK, MOSI, MISO",
        .frequency = "2.4GHz ISM",
    },
    {
        .name = "Address Scanner",
        .description = "Discover NRF24 device addresses",
        .type = NRF24ToolAddressScanner,
        .version = "1.7",
        .requires_nrf24_module = true,
        .gpio_pins = "CE(GPIO14), CSN(GPIO7), CLK, MOSI, MISO",
        .frequency = "2.4GHz ISM",
    },
};

#define NRF24_TOOLS_COUNT (sizeof(nrf24_tools) / sizeof(nrf24_tools[0]))

// Tool launcher
void launch_nrf24_tool(NRF24ToolType tool_type);

// Get tool by index
const NRF24Tool* get_nrf24_tool(int index);

// Get tool by name
const NRF24Tool* find_nrf24_tool_by_name(const char* name);

// Check NRF24 connection
bool check_nrf24_connection(void);

// Set NRF24 channel
void nrf24_set_channel(uint8_t channel);

// Get current channel
uint8_t nrf24_get_channel(void);

#endif // NRF24_TOOLS_H