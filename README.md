# customfirmware

FlipperZero Custom Firmware - Advanced UI System with Latest Momentum Apps & 12 Community Apps

## Overview

A complete custom UI framework for Flipper Zero firmware with modular view system, configurable themes, intuitive navigation, and integration with:
- **8 Momentum Official Apps** - Latest firmware tools
- **12 Community Apps** - Including games, emulators, and utilities

## Features

### UI System
- **Modern UI Framework**: Custom-built interface with consistent styling
- **Modular View Architecture**: Separate view components (Main, Settings, Apps, System)
- **Theme Support**: Light and dark themes with customizable colors
- **Settings Management**: Brightness, sound, vibration, and theme controls
- **Navigation Stack**: Stack-based view navigation for intuitive flow

### App Integration

#### 8 Momentum Official Apps
1. **RFID Explorer** - Scan and identify RFID tags
2. **NFC Tools** - Read/write NFC and automate devices
3. **Weather Decoder** - Decode weather station signals
4. **IR Remote** - Infrared remote control emulator
5. **Sub-GHz Scanner** - Advanced frequency scanning
6. **Bluetooth Finder** - Identify nearby Bluetooth devices
7. **Music Player** - Play tunes on your Flipper
8. **File Manager** - Advanced file navigation

#### 12 Community Apps
1. **HabitFlow** - Habit tracker with goals and streaks
2. **Stratagem Hero** - Helldivers 2-inspired tactical game
3. **Cell Lab** - Cellular automata simulator
4. **FlipRogue** - ASCII roguelike RPG
5. **Trivia Zero** - Bilingual flashcard trivia
6. **Sub-GHz Chat** - Device-to-device messaging
7. **Video Player** - Play video files
8. **Calculator** - Scientific calculator
9. **Bad USB** - USB keyboard/mouse emulator (Educational)
10. **WiFi Jammer** - Educational WiFi analyzer
11. **DemoBoy Simulator** - Game Boy emulator
12. **Climate Monitor** - Temperature/humidity monitoring

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

### Deploy to Flipper Zero

1. Connect device via USB
2. Use qFlipper to transfer binary
3. Run from Applications menu

## Architecture

### Core Components

- `src/ui/` - UI system and utilities
- `src/ui/views/` - Individual view implementations
- `src/apps/` - App launcher and app registry
- `examples/` - Usage examples
- `docs/` - Comprehensive documentation

### Views

- **Main View**: Menu-driven primary interface
- **Settings View**: System configuration options
- **Apps View**: Application launcher (Momentum + Community tabs)
- **System View**: System information and controls (planned)

## Navigation

- **UP/DOWN**: Navigate menu items / scroll apps
- **LEFT/RIGHT**: Adjust settings / switch app tabs
- **OK**: Select menu item / launch app
- **BACK**: Return to main menu / exit

## Documentation

- [ARCHITECTURE.md](docs/ARCHITECTURE.md) - System design and patterns
- [BUILDING.md](docs/BUILDING.md) - Build instructions
- [API.md](docs/API.md) - Complete API reference
- [APPS.md](docs/APPS.md) - All 20 apps documentation
- [MOMENTUM_INTEGRATION.md](docs/MOMENTUM_INTEGRATION.md) - Momentum firmware integration
- [CONTRIBUTING.md](CONTRIBUTING.md) - Contribution guidelines

## Examples

### Simple Application

```c
#include "ui/ui.h"

int main(void) {
    ui_init();
    
    // Use UI utilities
    UIConfig* config = ui_get_config();
    config->brightness = 200;
    ui_set_theme(UIThemeDark);
    
    // Your code here
    
    ui_deinit();
    return 0;
}
```

### Launch an App

```c
#include "apps/app_launcher.h"

// Launch Momentum app
launch_momentum_app(MomentumAppNFCTools);

// Launch community app
launch_community_app(CommunityAppCalculator);

// Find app by name
const MomentumApp* app = find_momentum_app_by_name("RFID Explorer");
const CommunityApp* com_app = find_community_app_by_name("DemoBoy Simulator");
```

## Momentum Integration

CustomFirmware is designed to work seamlessly with Momentum Firmware 012+:

- Full compatibility with Momentum apps
- Themed to match Momentum aesthetics
- Supports Momentum asset packs
- Compatible with JavaScript automation

See [MOMENTUM_INTEGRATION.md](docs/MOMENTUM_INTEGRATION.md) for details.

## Configuration

UI theme and settings are managed through `UIConfig` structure:

```c
UIConfig* config = ui_get_config();
config->brightness = 255;           // 0-255
config->vibration_enabled = true;
config->sound_enabled = true;
ui_set_theme(UIThemeDark);
```

## Extensibility

### Add New View

1. Create `src/ui/views/new_view.h|c`
2. Implement required functions
3. Register in view stack in `src/main.c`

### Add New App

1. Add to `MomentumAppType` or `CommunityAppType` enum
2. Add entry to app registry array
3. Implement launch logic

## CI/CD

Automated builds via GitHub Actions:

- **Linux**: GCC/Clang builds
- **macOS**: Clang builds
- **Windows**: MSVC builds
- **Code Quality**: clang-format validation

## Performance

- Optimized for 128x64 display
- Minimal memory footprint
- Efficient button input handling
- Low power consumption design

## License

MIT License - See [LICENSE](LICENSE) file

## Contributing

We welcome contributions! See [CONTRIBUTING.md](CONTRIBUTING.md) for guidelines.

## Changelog

See [CHANGELOG.md](CHANGELOG.md) for version history and updates.

## Resources

- **Flipper Zero**: https://flipperzero.one/
- **Momentum Firmware**: https://momentum-fw.dev/
- **Flipper SDK**: https://github.com/flipperdevices/flipperzero-firmware
- **Community Apps**: https://github.com/Next-Flip/Momentum-Apps
- **App Hub**: https://lab.flipper.net/apps/

## Support

For issues, questions, or suggestions:

1. Check [documentation](docs/)
2. Search [GitHub Issues](https://github.com/makajorden-netizen/customfirmware/issues)
3. Create new issue with details

## Disclaimer

This firmware is for educational purposes and authorized testing only. Users must comply with all applicable laws and regulations in their jurisdiction. All apps are provided for legal use only.
