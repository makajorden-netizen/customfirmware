# NRF24 Tools Documentation

## Overview

NRF24L01+ modules are 2.4GHz wireless transceivers commonly used in IoT devices, wireless mice/keyboards, and home automation. CustomFirmware includes comprehensive NRF24 tools integrated with Flipper Zero GPIO.

## ⚠️ Legal Notice

**ALL NRF24 TOOLS ARE FOR:**
- Educational purposes only
- Authorized testing on YOUR devices
- RF-shielded environments (for jamming)
- Security research with proper authorization

**ILLEGAL ACTIVITIES:**
- ❌ Interfering with others' devices
- ❌ Jamming outside labs/testing areas
- ❌ Unauthorized MouseJack attacks
- ❌ Transmitting without authorization

## NRF24 Tools Overview

### 1. Channel Scanner
- **Version**: 2.1
- **Description**: Scan 2.4GHz ISM band for NRF24 activity
- **Features**:
  - Scan channels 0-125 (2.400-2.525 GHz)
  - Detect signal strength
  - Identify active channels
  - Continuous or burst scan modes
  - Real-time channel display
- **Use Cases**: Network discovery, finding wireless devices

### 2. Packet Sniffer
- **Version**: 2.3
- **Description**: Passively capture NRF24 packets
- **Features**:
  - Capture raw packets on specific channels
  - Save captures to file
  - Packet structure analysis
  - MAC address discovery
  - Protocol identification
- **Use Cases**: Protocol reverse engineering, network analysis

### 3. MouseJacker
- **Version**: 1.8
- **Description**: Exploit Logitech Unifying receiver vulnerabilities
- **Features**:
  - Discover paired wireless mice
  - Intercept mouse commands
  - Inject movement/clicks
  - Logitech-specific payloads
  - Range testing
- **⚠️ WARNING**: Only use on devices you own
- **Targets**: Logitech wireless mice/keyboards, other vulnerable HID devices

### 4. Keyboard Jacker
- **Version**: 1.6
- **Description**: Intercept wireless keyboard communications
- **Features**:
  - Monitor keystrokes
  - Detect keyboard presence
  - Analyze key timing
  - Protocol analysis
  - Vulnerability detection
- **⚠️ WARNING**: Privacy concern - use only on your devices

### 5. Jammer
- **Version**: 1.9
- **Description**: 2.4GHz spectrum jammer for RF testing
- **Features**:
  - Transmit noise on 2.4GHz band
  - Channel selection
  - Power control
  - Burst/continuous modes
  - Frequency hopping
- **⚠️⚠️ CRITICAL**: ILLEGAL outside RF-shielded labs!
  - Violates FCC regulations
  - Can interfere with vital services
  - Heavy fines and criminal penalties
  - Use ONLY in Faraday cage

### 6. Payload Transmitter
- **Version**: 2.0
- **Description**: Create and transmit custom NRF24 payloads
- **Features**:
  - Custom payload editor
  - Address configuration
  - Transmission power control
  - Retry logic
  - Acknowledgment handling
- **Use Cases**: Testing device firmware, protocol development

### 7. Address Scanner
- **Version**: 1.7
- **Description**: Discover NRF24 device addresses
- **Features**:
  - Brute force address discovery
  - Identify active pipes
  - Scan speed control
  - Address pattern detection
  - Save discovered addresses
- **Use Cases**: Device inventory, network mapping

## Hardware Setup

### NRF24L01+ Module Pinout

```
NRF24 Pin | Description | Flipper GPIO
---------+--------------+-----------
1         | GND          | GND (Pin 8 or 11)
2         | VCC (3.3V)   | 3.3V (Pin 9)
3         | CE           | GPIO14
4         | CSN/CS       | GPIO7
5         | SCK          | GPIO6 (SPI CLK)
6         | MOSI         | GPIO5 (SPI MOSI)
7         | MISO         | GPIO4 (SPI MISO)
8         | IRQ          | GPIO3 (optional)
```

### Wiring Checklist
- ✅ Power: 3.3V (NOT 5V - will damage module)
- ✅ GND properly connected
- ✅ CE pin on GPIO14
- ✅ CSN pin on GPIO7
- ✅ SPI lines properly connected
- ✅ Antenna installed
- ✅ Capacitor (10µF) across power pins

## Channel Reference

### 2.4GHz ISM Band

```
Channel | Frequency   | Usage
--------|-------------|-------------------
0-76    | 2.400-2.476 | WiFi + NRF24
77-83   | 2.477-2.483 | WiFi + NRF24
84-125  | 2.484-2.525 | Region specific
```

### Common Channels by Device
- **Logitech Unifying**: Channels 3, 30, 55, 70 (hops)
- **Generic devices**: Often channels 76-125
- **WiFi interference**: Avoid channels 1, 6, 11, 36, 40, 44, 48

## Usage Examples

### Launch NRF24 Tool

```c
#include "apps/nrf24_tools.h"

// Launch channel scanner
launch_nrf24_tool(NRF24ToolChannelScanner);

// Launch MouseJacker
launch_nrf24_tool(NRF24ToolMouseJacker);

// Find and launch by name
const NRF24Tool* tool = find_nrf24_tool_by_name("Packet Sniffer");
if(tool) {
    launch_nrf24_tool(tool->type);
}
```

### Channel Management

```c
#include "apps/nrf24_tools.h"

// Set channel for scanning
nrf24_set_channel(76);

// Get current channel
uint8_t ch = nrf24_get_channel();
furi_log_info("NRF24", "Current channel: %d", ch);

// Check connection
if(check_nrf24_connection()) {
    furi_log_info("NRF24", "Module connected");
}
```

## Safety Guidelines

### For Channel Scanning
✅ Safe in any environment
✅ Non-intrusive passive observation
✅ No regulatory issues

### For Packet Sniffing
✅ Safe if on your own network
✅ Passive monitoring only
⚠️ Respect privacy laws

### For MouseJack/Keyboard
⚠️ Only on YOUR devices
⚠️ Only for testing purposes
⚠️ Never on others' equipment

### For Jamming
🔴 **ONLY in RF-shielded enclosure**
🔴 **Never in open environment**
🔴 **Verify no interference with vital services**
🔴 **Criminal penalties apply for misuse**

## Troubleshooting

### Module Not Detected
- Check 3.3V power supply (not 5V)
- Verify GPIO pin connections
- Check SPI line continuity
- Add bypass capacitor (10µF)

### Can't Find Devices
- Verify devices are powered on
- Try different channels
- Increase scan duration
- Check antenna connection

### Weak Signal
- Check antenna orientation
- Reduce distance from target
- Try different channels
- Verify module power supply

### Injection Fails
- Verify target channel
- Check payload format
- Confirm device in range
- Try different power levels

## Resources

- **GitHub**: https://github.com/huuck/FlipperZeroNRFJammer
- **nrf24tool**: https://github.com/OuinOuin74/nrf24tool
- **Flipper Lab**: https://lab.flipper.net/apps/nrf24channelscanner
- **NRF24 Datasheet**: https://www.nordicsemi.com/Products/nRF24L01

## Disclaimer

These tools are for authorized security testing only. Users are responsible for:
- Understanding local RF regulations
- Obtaining proper authorization
- Operating only on devices they own
- Not interfering with others' communications
- Following FCC/ETSI guidelines

Misuse of these tools may result in:
- Civil penalties
- Criminal charges
- Hardware confiscation
- Fines up to $100,000+

Use responsibly and legally.
