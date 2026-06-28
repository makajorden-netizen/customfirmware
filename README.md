# customfirmware

FlipperZero Custom Firmware - Advanced UI System with 20+ Apps Including BLE Spam, ESP32 Tools & Advanced RF

## Overview

A complete custom UI framework for Flipper Zero firmware with:
- **Modern UI Framework** with modular views and themes
- **20 Community & Momentum Apps**
- **7 Advanced Hacking/Security Research Tools** (BLE Spam, WiFi, RF)
- **6 ESP32 Integration Tools** for GPIO-based ESP32 module control
- **Professional Documentation** and examples

## Features

### UI System
- Modern interface with consistent styling
- Modular view architecture (Main, Settings, Apps, System)
- Light and dark themes with customizable colors
- Settings management (brightness, sound, vibration)
- Stack-based view navigation

### Apps Included

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

#### 7 Advanced Tools
1. **BLE Spam** - Bluetooth notification attacks
2. **ESP32 Marauder** - WiFi & BLE scanning with ESP32 module
3. **WiFi War Drive** - Map networks with GPS
4. **BT Beacon Spoof** - Spoof Bluetooth beacons
5. **RF Signal Analyzer** - Advanced signal analysis
6. **Deauther** - WiFi deauth testing tool
7. **Packet Sniffer** - Network packet capture

#### 6 ESP32 Tools (GPIO Control)
1. WiFi Scanner
2. BLE Scanner
3. Packet Capture
4. Firmware Flasher
5. GPIO Controller
6. Programmer

## Quick Start

### Build

```bash
mkdir build
cd build
cmake ..
make
```

### Run

```bash
./build/customfirmware_app
```

### Deploy

1. Connect Flipper Zero via USB
2. Use qFlipper to transfer
3. Run from Applications

## App Navigation

- **UP/DOWN**: Navigate menu items
- **LEFT/RIGHT**: Switch between app categories (Momentum/Community/Advanced/ESP32)
- **OK**: Launch selected app
- **BACK**: Return to previous menu

## Documentation

- [ARCHITECTURE.md](docs/ARCHITECTURE.md) - System design
- [BUILDING.md](docs/BUILDING.md) - Build instructions
- [API.md](docs/API.md) - API reference
- [APPS.md](docs/APPS.md) - Community apps (20 apps)
- [ADVANCED_APPS.md](docs/ADVANCED_APPS.md) - Advanced tools & ESP32 integration
- [MOMENTUM_INTEGRATION.md](docs/MOMENTUM_INTEGRATION.md) - Momentum firmware
- [CONTRIBUTING.md](CONTRIBUTING.md) - How to contribute

## Advanced Apps Usage

### Launch BLE Spam

```c
#include "apps/advanced_apps.h"

launch_advanced_app(AdvancedAppBLESpam);
```

### Launch ESP32 Marauder

```c
#include "apps/advanced_apps.h"

launch_advanced_app(AdvancedAppESP32Marauder);
```

### Control ESP32 GPIO

```c
#include "apps/esp32_tools.h"

launch_esp32_tool(ESP32ToolWiFiScanning);
if(check_esp32_connection()) {
    // ESP32 connected and ready
}
```

## ESP32 Marauder Hardware

### GPIO Connection

```
ESP32 TX  -> Flipper RX (Pin 13)
ESP32 RX  -> Flipper TX (Pin 12)
ESP32 GND -> Flipper GND (Pin 8 or 11)
ESP32 5V  -> Flipper 5V (Pin 1)
```

### Features
- WiFi network scanning
- BLE device discovery
- Packet capture
- Deauthentication attacks
- Beacon spoofing
- Signal strength mapping

## ⚠️ Legal Notice

All advanced tools are for:
- **Educational purposes only**
- **Authorized testing** (networks/devices you own)
- **Security research** in controlled environments

**Unauthorized use may violate local laws.**

Users are responsible for:
- Knowing wireless regulations in their jurisdiction
- Obtaining proper authorization before testing
- Complying with FCC/ETSI regulations
- Respecting privacy and security laws

## Configuration

```c
UIConfig* config = ui_get_config();
config->brightness = 255;           // 0-255
config->vibration_enabled = true;
config->sound_enabled = true;
ui_set_theme(UIThemeDark);
```

## Extensibility

### Add New Advanced App

1. Add to enum in `advanced_apps.h`
2. Add entry to `advanced_apps[]` array
3. Add case in `launch_advanced_app()` switch

### Add New ESP32 Tool

1. Add to enum in `esp32_tools.h`
2. Add entry to `esp32_tools[]` array
3. Implement in `esp32_tools.c`

## CI/CD

- Automated builds on Linux, macOS, Windows
- Code quality checks with clang-format
- GitHub Actions workflows

## Performance

- Optimized for 128x64 display
- Minimal memory footprint
- Efficient GPIO communication
- Low power consumption

## License

MIT License - See [LICENSE](LICENSE)

## Contributing

See [CONTRIBUTING.md](CONTRIBUTING.md)

## Resources

- **Flipper Zero**: https://flipperzero.one/
- **Momentum**: https://momentum-fw.dev/
- **ESP32 Marauder**: https://github.com/justcallmekoko/ESP32Marauder
- **BLE Spam**: https://github.com/EvanDebruyne/Flipper-Zero-BLE-Spam
- **Flipper SDK**: https://github.com/flipperdevices/flipperzero-firmware

## Support

1. Check documentation
2. Search GitHub issues
3. Create new issue with details

## Disclaimer

This firmware is for educational and authorized use only. Users must comply with all applicable laws and regulations. Use responsibly.
