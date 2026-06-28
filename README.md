# customfirmware

FlipperZero Custom Firmware - 35 Total Apps: Momentum + Community + Advanced + ESP32 + NRF24 + **Wireshark**

## Overview

The ultimate Flipper Zero firmware with comprehensive app ecosystem:
- **8 Momentum Official Apps**
- **12 Community Apps** (games, utilities, emulators)
- **7 Advanced Hacking Tools** (BLE, WiFi, RF)
- **6 ESP32 GPIO Tools** (WiFi scanning, BLE, packet capture)
- **7 NRF24 2.4GHz Tools** (MouseJack, sniffing, jamming)
- **1 ESP32 Wireshark** ✅ **NEW** - Professional packet capture & analysis
- **Professional UI Framework** with themes and navigation
- **Complete Documentation** with legal notices

## Features

### UI System
- Modern interface with consistent styling
- Modular view architecture (Main, Settings, Apps, System)
- Light and dark themes
- Settings management
- Stack-based navigation

### 35 Integrated Apps

#### 8 Momentum Official Apps
1. RFID Explorer
2. NFC Tools
3. Weather Decoder
4. IR Remote
5. Sub-GHz Scanner
6. Bluetooth Finder
7. Music Player
8. File Manager

#### 12 Community Apps
1. HabitFlow
2. Stratagem Hero
3. Cell Lab
4. FlipRogue
5. Trivia Zero
6. Sub-GHz Chat
7. Video Player
8. Calculator
9. Bad USB
10. WiFi Jammer
11. DemoBoy Simulator
12. Climate Monitor

#### 7 Advanced Security Tools
1. BLE Spam
2. ESP32 Marauder
3. WiFi War Drive
4. BT Beacon Spoof
5. RF Signal Analyzer
6. Deauther
7. Packet Sniffer

#### 6 ESP32 GPIO Tools
1. WiFi Scanner
2. BLE Scanner
3. Packet Capture
4. Firmware Flasher
5. GPIO Controller
6. Programmer

#### 7 NRF24 2.4GHz Tools
1. Channel Scanner
2. Packet Sniffer
3. MouseJacker
4. Keyboard Jacker
5. Jammer
6. Payload Transmitter
7. Address Scanner

#### 1 ESP32 Wireshark ✅ **NEW**
- **Professional Network Capture** - Real-time WiFi/BLE packet capture
- **Wireshark Compatible** - Export to PCAP format for Wireshark analysis
- **Multi-Format Export** - PCAP, CSV, JSON export formats
- **Advanced Filtering** - Channel, MAC, RSSI, packet type filters
- **Live Statistics** - Real-time packet stats and signal analysis
- **Buffer Management** - 1,000 packet buffer with overflow handling
- **Deep Analysis** - Packet-level inspection and metadata extraction

## Quick Start

### Build

```bash
mkdir build && cd build
cmake ..
make
```

### Deploy

1. Connect Flipper Zero via USB
2. Use qFlipper to transfer binary
3. Run from Applications menu

## ESP32 Wireshark Features

### Real-Time Packet Capture

✅ **WiFi Packets:**
- Data frames (TCP/UDP traffic frames)
- Management frames (auth, assoc, beacon, probe)
- Deauthentication frames
- Full 802.11 frame analysis
- Per-packet RSSI and data rate

✅ **Bluetooth Packets:**
- BLE advertisements
- BLE connection data
- Raw BLE payloads
- Device discovery

### Export Formats

**PCAP Format (Wireshark Compatible)**
```bash
wireshark capture.pcap
tcpdump -r capture.pcap
```

**CSV Format (Spreadsheet Ready)**
```csv
Number,Time,Source,Destination,Protocol,Length,RSSI,Channel,Type
1,1234.567,AA:BB:CC:DD:EE:FF,FF:FF:FF:FF:FF:FF,802.11n,256,-45,6,WiFi Data
```

**JSON Format (Programmatic Analysis)**
```json
{
  "packets": [...],
  "statistics": {
    "total_packets": 1000,
    "wifi_packets": 850,
    "ble_packets": 150
  }
}
```

### Advanced Filtering

```c
WiresharkFilter filter = {
    .capture_wifi_data = true,
    .capture_wifi_mgmt = false,
    .capture_ble_adv = true,
    .min_signal_strength = -60,    // RSSI threshold
    .target_channel = 6,            // Specific channel
};
strcpy(filter.filter_mac, "AA:BB:CC:DD:EE:FF");
wireshark_set_filter(session, &filter);
```

### Live Statistics

```c
WiresharkStats stats = wireshark_get_stats(session);
- Total packets captured
- WiFi vs BLE breakdown
- Signal strength (min/max/avg RSSI)
- Packet type distribution
- Dropped packet count
```

## NRF24 Hardware Setup

### GPIO Connection

```
NRF24 Pin | Flipper GPIO
----------|------------------
GND       | GND (Pin 8/11)
VCC (3.3V)| 3.3V (Pin 9)
CE        | GPIO14
CSN       | GPIO7
SCK       | GPIO6 (SPI)
MOSI      | GPIO5 (SPI)
MISO      | GPIO4 (SPI)
IRQ       | GPIO3 (optional)
```

### ⚠️ Important
- **Use 3.3V, NOT 5V** (will damage module)
- Add 10µF bypass capacitor across power
- Verify antenna is installed
- Keep SPI lines short

## Channel Reference

**NRF24 Channels**: 0-125 (2.400-2.525 GHz)
**WiFi Channels**: 1-13 (2.4GHz), 36-165 (5GHz)

Common channels by device:
- **Logitech Unifying**: 3, 30, 55, 70 (hops)
- **Generic**: 76-125
- **Avoid WiFi interference**: Avoid channels 1, 6, 11, 36, 40, 44, 48

## App Navigation

- **UP/DOWN**: Navigate menu items
- **LEFT/RIGHT**: Switch app categories
- **OK**: Launch app
- **BACK**: Return/Exit

## Documentation

- [ARCHITECTURE.md](docs/ARCHITECTURE.md) - System design
- [BUILDING.md](docs/BUILDING.md) - Build instructions
- [API.md](docs/API.md) - API reference
- [APPS.md](docs/APPS.md) - Community apps (20)
- [ADVANCED_APPS.md](docs/ADVANCED_APPS.md) - Advanced tools & ESP32
- [NRF24_TOOLS.md](docs/NRF24_TOOLS.md) - NRF24 2.4GHz tools
- [ESP32_WIRESHARK.md](docs/ESP32_WIRESHARK.md) - **Packet capture & analysis** ✅ **NEW**
- [MOMENTUM_INTEGRATION.md](docs/MOMENTUM_INTEGRATION.md) - Momentum

## Usage Examples

### ESP32 Wireshark - Basic Capture

```c
#include "apps/esp32_wireshark.h"

// Initialize
WiresharkSession* session = wireshark_init();
wireshark_start_capture(session);

// Capture for 60 seconds
furi_delay_ms(60000);

// Export to Wireshark format
wireshark_export_pcap(session, "/ext/captures/network.pcap");
wireshark_export_csv(session, "/ext/captures/network.csv");
wireshark_export_json(session, "/ext/captures/network.json");

// Get statistics
WiresharkStats stats = wireshark_get_stats(session);
furi_log_info("WIRESHARK", "Packets: %ld | WiFi: %ld | BLE: %ld",
    stats.total_packets, stats.wifi_packets, stats.ble_packets);

wireshark_free(session);
```

### ESP32 Wireshark - Advanced Filtering

```c
// Set channel and RSSI filter
WiresharkFilter filter = {
    .capture_wifi_data = true,
    .capture_ble_adv = false,
    .min_signal_strength = -60,
    .target_channel = 6,
};
wireshark_set_filter(session, &filter);
```

### NRF24 - Launch Tools

```c
#include "apps/nrf24_tools.h"

// Launch channel scanner
launch_nrf24_tool(NRF24ToolChannelScanner);

// Launch packet sniffer
launch_nrf24_tool(NRF24ToolPacketSniffer);
```

## Safety & Legal

### ✅ Legal Uses
- Testing YOUR OWN devices
- Security research with authorization
- RF-shielded lab testing
- Educational purposes
- Network troubleshooting

### ❌ Illegal Uses
- Interfering with others' devices
- Jamming outside labs
- Unauthorized attacks
- Privacy violations
- Capturing others' traffic without consent

## ⚠️ NRF24 Jamming

**CRITICAL**: Jamming is **ILLEGAL** outside RF-shielded environments
- Violates FCC regulations
- Criminal penalties apply
- Fines up to $100,000+
- Use ONLY in Faraday cage

## ⚠️ Wireshark/Packet Capture

**Legal Notice:**
- Only capture traffic on networks you own/have permission to access
- Do not use to intercept others' communications
- Comply with all local wiretapping and privacy laws
- Use for authorized security testing only

## Resources

- **Wireshark Official**: https://www.wireshark.org/
- **ESP32 Wireshark Docs**: docs/ESP32_WIRESHARK.md
- **NRF24 Jammer**: https://github.com/huuck/FlipperZeroNRFJammer
- **nrf24tool**: https://github.com/OuinOuin74/nrf24tool
- **Flipper Lab**: https://lab.flipper.net/apps
- **ESP32 Marauder**: https://github.com/justcallmekoko/ESP32Marauder
- **Momentum**: https://momentum-fw.dev/

## Configuration

```c
UIConfig* config = ui_get_config();
config->brightness = 255;
config->vibration_enabled = true;
config->sound_enabled = true;
ui_set_theme(UIThemeDark);
```

## CI/CD

- Automated builds (Linux, macOS, Windows)
- Code quality checks
- GitHub Actions workflows

## License

MIT License - See [LICENSE](LICENSE)

## Contributing

See [CONTRIBUTING.md](CONTRIBUTING.md)

## Disclaimer

This firmware is for educational and authorized use only. Users are responsible for:
- Understanding local RF regulations
- Operating within legal boundaries
- Obtaining proper authorization
- Complying with FCC/ETSI guidelines
- Respecting privacy laws

**Misuse may result in civil and criminal penalties.**
