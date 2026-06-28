# Advanced Apps & ESP32 Tools

## Overview

CustomFirmware includes advanced hacking, security research, and RF analysis tools integrated with Momentum firmware and standalone community tools.

## ⚠️ Legal Notice

**All advanced tools are for:**
- Educational purposes
- Authorized testing only
- Networks/devices you own or have explicit permission to test
- Security research in controlled environments

Unauthorized use may violate local laws.

## Bluetooth Advanced Apps

### 1. BLE Spam
- **Description**: Bluetooth spam and notification attack tool
- **Version**: 2.3
- **Category**: Bluetooth
- **Features**:
  - Generate fake BLE advertisements
  - Spoof notifications (AirDrop, device setup, etc.)
  - Randomized MAC addresses
  - Adjustable spam frequency
  - Educational signal analysis
- **Note**: Effectiveness varies by device and OS version. Newer iOS/Android devices have mitigations in place.

### 2. BT Beacon Spoof
- **Description**: Spoof Bluetooth beacon signals
- **Version**: 1.5
- **Category**: Bluetooth
- **Features**:
  - Create fake iBeacon signals
  - Spoof Eddystone beacons
  - Customize beacon parameters
  - Test beacon detection
- **Use Cases**: Testing beacon-based apps, proximity testing

## WiFi Advanced Apps

### 3. WiFi War Drive
- **Description**: Map WiFi networks with GPS data
- **Version**: 1.8
- **Category**: WiFi
- **Features**:
  - Scan nearby WiFi networks
  - GPS location tagging (requires GPS module)
  - Network strength mapping
  - Save scan results
  - Generate network maps
- **Requirements**: GPS module for location data

### 4. Deauther
- **Description**: WiFi deauthentication attack tool
- **Version**: 2.4
- **Category**: WiFi
- **Features**:
  - Scan WiFi networks
  - Send deauth frames
  - Disconnect devices (for testing)
  - Frame control
  - Channel monitoring
- **⚠️ Warning**: Only use on networks you own or have permission to test

### 5. Packet Sniffer
- **Description**: Capture and analyze network packets
- **Version**: 1.9
- **Category**: WiFi
- **Features**:
  - Capture WiFi packets
  - Protocol analysis
  - Filter by protocol/MAC
  - Save packet captures
  - Decrypt WEP (legacy)
- **Requires**: WiFi analysis capabilities

## RF & Signal Analysis

### 6. RF Signal Analyzer
- **Description**: Advanced RF signal analysis
- **Version**: 2.0
- **Category**: RF
- **Features**:
  - Analyze Sub-GHz signals
  - Signal strength visualization
  - Frequency mapping
  - Protocol identification
  - Signal recording

## ESP32 Integration Apps

### 7. ESP32 Marauder
- **Description**: WiFi & Bluetooth scanning with ESP32 module
- **Version**: 3.1
- **Category**: ESP32
- **Author**: justcallmekoko
- **Features**:
  - WiFi network scanning
  - BLE device scanning
  - Packet capture
  - WiFi access point spoofing
  - Beacon frame generation
  - Deauthentication attacks
  - Network security testing
- **Requires**: ESP32 module connected to Flipper GPIO
- **GitHub**: https://github.com/justcallmekoko/ESP32Marauder

## ESP32 Tools (GPIO-Based)

Direct ESP32 module control and integration:

### 1. WiFi Scanner
- Scan available WiFi networks
- Get signal strength (RSSI)
- Identify security types
- Channel information

### 2. BLE Scanner
- Scan Bluetooth devices
- Capture advertisement data
- Signal strength measurement
- Device identification

### 3. Packet Capture
- Capture network traffic
- Save to file
- Protocol filtering
- Real-time analysis

### 4. Firmware Flasher
- Flash ESP32 firmware via GPIO
- Automatic bootloader detection
- Progress monitoring
- Verify after flashing

### 5. GPIO Controller
- Control individual GPIO pins
- Set pin modes (input/output)
- Read/write digital values
- PWM control
- Timing control

### 6. Programmer
- Program ESP32 via UART
- Upload sketches
- Serial monitor
- Baud rate selection

## ESP32 Marauder Hardware Setup

### Requirements
- ESP32 development board (or compatible)
- Flipper Zero with GPIO access
- USB-to-serial adapter (optional)
- Jumper wires

### GPIO Connection
```
ESP32 GPIO -> Flipper Zero GPIO

ESP32 TX (GPIO 1)  -> Flipper RX (Pin 13)
ESP32 RX (GPIO 3)  -> Flipper TX (Pin 12)
ESP32 GND          -> Flipper GND (Pin 8 or 11)
ESP32 5V/3.3V      -> Flipper 5V (Pin 1) or 3.3V (Pin 9)
```

### Firmware Installation

1. Download ESP32 Marauder firmware
2. Use ESP32 Firmware Flasher tool
3. Connect ESP32 to Flipper GPIO
4. Follow on-screen instructions
5. Test connection

## App Launcher Integration

### Launch Advanced App
```c
#include "apps/advanced_apps.h"

// Launch BLE Spam
launch_advanced_app(AdvancedAppBLESpam);

// Launch ESP32 Marauder
launch_advanced_app(AdvancedAppESP32Marauder);

// Find by name
const AdvancedApp* app = find_advanced_app_by_name("WiFi War Drive");
if(app) {
    launch_advanced_app(app->type);
}
```

### Launch ESP32 Tool
```c
#include "apps/esp32_tools.h"

// Launch WiFi scanner
launch_esp32_tool(ESP32ToolWiFiScanning);

// Check ESP32 connection
if(check_esp32_connection()) {
    furi_log_info("ESP32", "Connection OK");
}
```

## Safety & Best Practices

### WiFi Testing
- ✅ Only test networks you own
- ✅ Get written permission before testing others' networks
- ✅ Use isolated test environment when possible
- ❌ Don't use tools maliciously
- ❌ Don't interfere with critical infrastructure

### Bluetooth Testing
- ✅ Test in controlled environment
- ✅ Document all testing
- ✅ Limit spam to short bursts
- ❌ Don't target specific individuals
- ❌ Don't use in public without consent

### RF Testing
- ✅ Stay within legal frequency ranges for your region
- ✅ Know transmission power limits
- ✅ Test antennas safely
- ❌ Don't transmit on protected frequencies
- ❌ Don't interfere with licensed operators

## Resources

- **ESP32 Marauder**: https://github.com/justcallmekoko/ESP32Marauder
- **BLE Spam**: https://github.com/EvanDebruyne/Flipper-Zero-BLE-Spam
- **Flipper GPIO**: https://docs.flipperzero.one/
- **ESP32 Docs**: https://docs.espressif.com/

## Troubleshooting

### ESP32 Connection Failed
- Check GPIO wiring
- Verify TX/RX pins (often swapped)
- Confirm power supply
- Test with multimeter

### BLE Spam Not Working
- Verify Bluetooth is enabled
- Check Flipper BLE module
- Update firmware
- Ensure target device in range

### WiFi Tools Not Scanning
- Verify WiFi radio is enabled
- Check antenna connection
- Update driver firmware
- Test with simple scan first

## Legal Compliance

Users are responsible for:
- Knowing local wireless laws
- Obtaining proper authorization
- Following FCC/ETSI regulations
- Respecting privacy laws
- Keeping detailed documentation

Viewing or using these tools constitutes agreement to use them legally and responsibly.
