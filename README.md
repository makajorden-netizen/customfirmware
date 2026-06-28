# customfirmware

FlipperZero Custom Firmware - 34 Total Apps: Momentum + Community + Advanced + ESP32 + NRF24

## Overview

The ultimate Flipper Zero firmware with comprehensive app ecosystem:
- **8 Momentum Official Apps**
- **12 Community Apps** (games, utilities, emulators)
- **7 Advanced Hacking Tools** (BLE, WiFi, RF)
- **6 ESP32 GPIO Tools** (WiFi scanning, BLE, packet capture)
- **7 NRF24 2.4GHz Tools** (MouseJack, sniffing, jamming)
- **Professional UI Framework** with themes and navigation
- **Complete Documentation** with legal notices

## Features

### UI System
- Modern interface with consistent styling
- Modular view architecture (Main, Settings, Apps, System)
- Light and dark themes
- Settings management
- Stack-based navigation

### 34 Integrated Apps

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

#### 7 NRF24 2.4GHz Tools ✅ **NEW**
1. **Channel Scanner** - 2.4GHz activity detection
2. **Packet Sniffer** - Capture NRF24 packets
3. **MouseJacker** - Exploit wireless mice/keyboards
4. **Keyboard Jacker** - Intercept keyboard communications
5. **Jammer** - 2.4GHz spectrum jammer (RF-shielded only)
6. **Payload Transmitter** - Custom NRF24 payload crafting
7. **Address Scanner** - Discover NRF24 addresses

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
- [MOMENTUM_INTEGRATION.md](docs/MOMENTUM_INTEGRATION.md) - Momentum

## Usage Examples

### Launch NRF24 Tool

```c
#include "apps/nrf24_tools.h"

// Channel scanner
launch_nrf24_tool(NRF24ToolChannelScanner);

// MouseJacker
launch_nrf24_tool(NRF24ToolMouseJacker);

// Find by name
const NRF24Tool* tool = find_nrf24_tool_by_name("Packet Sniffer");
if(tool) launch_nrf24_tool(tool->type);
```

### Channel Control

```c
#include "apps/nrf24_tools.h"

// Set channel
nrf24_set_channel(76);

// Get current
uint8_t ch = nrf24_get_channel();

// Check connection
if(check_nrf24_connection()) {
    // Module connected
}
```

## Safety & Legal

### ✅ Legal Uses
- Testing YOUR OWN devices
- Security research with authorization
- RF-shielded lab testing
- Educational purposes

### ❌ Illegal Uses
- Interfering with others' devices
- Jamming outside labs
- Unauthorized attacks
- Privacy violations

## ⚠️ NRF24 Jamming

**CRITICAL**: Jamming is **ILLEGAL** outside RF-shielded environments
- Violates FCC regulations
- Criminal penalties apply
- Fines up to $100,000+
- Use ONLY in Faraday cage

## Resources

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

**Misuse may result in civil and criminal penalties.**
