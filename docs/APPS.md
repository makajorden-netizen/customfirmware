# Apps Documentation

## Overview

CustomFirmware includes integration with the latest Momentum firmware apps and popular community applications for Flipper Zero.

## Momentum Apps (Official)

Momentum is the most feature-rich custom firmware for Flipper Zero. Our custom UI integrates all major Momentum apps:

### 1. RFID Explorer
- **Description**: Explore and detect RFID tags and cards
- **Version**: 2.1
- **Features**:
  - Scan and identify RFID cards
  - Store captured cards
  - Analyze signal patterns
  - Educational learning mode

### 2. NFC Tools
- **Description**: Read, write, and emulate NFC tags
- **Version**: 2.0
- **Features**:
  - Read NFC tags
  - Write custom data
  - Automate home devices
  - Tag emulation
  - Amiibo support

### 3. Weather Decoder
- **Description**: Decode wireless signals from weather stations
- **Version**: 1.5
- **Features**:
  - Decode weather station protocols
  - Sub-GHz signal analysis
  - Educational signal learning
  - Protocol visualization

### 4. IR Remote
- **Description**: Infrared remote control emulator
- **Version**: 2.2
- **Features**:
  - Control TVs, projectors, soundbars
  - Record IR signals
  - Create custom remotes
  - Large device database

### 5. Sub-GHz Scanner
- **Description**: Advanced Sub-GHz frequency scanner
- **Version**: 2.3
- **Features**:
  - Scan wireless frequencies
  - Identify home automation devices
  - Signal strength display
  - Educational signal exploration

### 6. Bluetooth Finder
- **Description**: Identify nearby Bluetooth devices
- **Version**: 1.8
- **Features**:
  - Detect active Bluetooth devices
  - Signal strength measurement
  - Device name identification
  - Educational purposes

### 7. Music Player
- **Description**: Play audio on your Flipper
- **Version**: 1.2
- **Features**:
  - Play tunes and melodies
  - Custom audio support
  - Simple notation

### 8. File Manager
- **Description**: Advanced file navigation and management
- **Version**: 2.4
- **Features**:
  - Browse and organize files
  - Transfer files via USB
  - Manage settings
  - Backup and restore

## Community Apps

Popular community-developed applications available in our app launcher:

### 1. HabitFlow
- **Description**: Offline habit tracker with goals and streaks
- **Author**: Community
- **Version**: 1.3
- **GitHub**: flipper-zero/HabitFlow
- **Features**:
  - Track daily habits
  - Goal setting
  - Streak counting
  - Progress visualization

### 2. Stratagem Hero
- **Description**: Helldivers 2-inspired tactical game
- **Author**: Community
- **Version**: 2.1
- **GitHub**: flipper-zero/stratagem-hero
- **Features**:
  - Tactical gameplay
  - Strategy based
  - Score tracking

### 3. Cell Lab
- **Description**: Tiny pixel world simulator
- **Author**: Community
- **Version**: 1.5
- **GitHub**: flipper-zero/cell-lab
- **Features**:
  - Cellular automata simulation
  - Interactive sandbox
  - Pattern creation

### 4. FlipRogue
- **Description**: ASCII roguelike RPG adventure
- **Author**: Community
- **Version**: 1.2
- **GitHub**: flipper-zero/fliprogue
- **Features**:
  - Dungeon exploration
  - RPG mechanics
  - Turn-based combat
  - Procedurally generated levels

### 5. Trivia Zero
- **Description**: Bilingual flashcard trivia game
- **Author**: Community
- **Version**: 1.4
- **GitHub**: flipper-zero/trivia-zero
- **Features**:
  - Multiple languages
  - Flashcard learning
  - Score tracking
  - Custom card sets

### 6. Sub-GHz Chat
- **Description**: Send text messages over Sub-GHz
- **Author**: Community
- **Version**: 1.6
- **GitHub**: flipper-zero/subghz-chat
- **Features**:
  - Device-to-device messaging
  - Sub-GHz protocol
  - Long range
  - Simple interface

### 7. Video Player
- **Description**: Play video files on display
- **Author**: Community
- **Version**: 1.1
- **GitHub**: flipper-zero/video-player
- **Features**:
  - Supported formats: H.264, MJPEG
  - Speed control
  - Frame-by-frame

### 8. Calculator
- **Description**: Full-featured scientific calculator
- **Author**: Community
- **Version**: 2.0
- **GitHub**: flipper-zero/calculator
- **Features**:
  - Basic arithmetic
  - Scientific functions
  - History tracking
  - Programmable

### 9. Bad USB
- **Description**: USB keyboard/mouse emulator (Educational)
- **Author**: Community
- **Version**: 2.5
- **GitHub**: flipper-zero/badusb
- **Features**:
  - Keyboard emulation
  - Mouse emulation
  - Custom payload scripting
  - Authorized testing only

### 10. WiFi Jammer
- **Description**: Educational WiFi signal analyzer
- **Author**: Community
- **Version**: 1.9
- **GitHub**: flipper-zero/wifi-jammer
- **Features**:
  - WiFi network scanning
  - Signal analysis
  - Channel visualization
  - Educational learning

### 11. DemoBoy Simulator
- **Description**: Game Boy emulator
- **Author**: Community
- **Version**: 1.7
- **GitHub**: flipper-zero/demoboy
- **Features**:
  - Play classic Game Boy games
  - Save/load states
  - Full color support
  - Peripherals support

### 12. Climate Monitor
- **Description**: Temperature and humidity monitor
- **Author**: Community
- **Version**: 1.0
- **GitHub**: flipper-zero/climate-monitor
- **Features**:
  - Real-time monitoring
  - Sensor integration
  - Data logging
  - Threshold alerts

## App Integration

### Using the Apps View

The custom UI provides a dedicated apps view:

```c
#include "ui/views/apps_view.h"
#include "apps/app_launcher.h"

// Allocate apps view
View* apps_view = apps_view_alloc();

// Set callback when app is selected
apps_view_set_callback(apps_view, on_app_selected);

static void on_app_selected(const char* app_name) {
    furi_log_info("APPS", "Launching: %s", app_name);
    
    // Find and launch app
    const MomentumApp* momentum = find_momentum_app_by_name(app_name);
    if(momentum) {
        launch_momentum_app(momentum->type);
        return;
    }
    
    const CommunityApp* community = find_community_app_by_name(app_name);
    if(community) {
        launch_community_app(community->type);
    }
}
```

### Navigation in Apps View

- **UP/DOWN**: Navigate app list
- **LEFT/RIGHT**: Switch between Momentum and Community tabs
- **OK**: Launch selected app
- **BACK**: Return to main menu

## Adding New Apps

### To Add a Momentum App:

1. Add enum value to `MomentumAppType` in `src/apps/momentum_apps.h`
2. Add app entry to `momentum_apps[]` array
3. Add launch case in `launch_momentum_app()` function

### To Add a Community App:

1. Add enum value to `CommunityAppType` in `src/apps/community_apps.h`
2. Add app entry to `community_apps[]` array
3. Add launch case in `launch_community_app()` function

### Example:

```c
// In community_apps.h
typedef enum {
    // ...
    CommunityAppMyNewApp,
    CommunityAppCount,
} CommunityAppType;

// In community_apps.c (community_apps array)
{
    .name = "My New App",
    .description = "Description here",
    .type = CommunityAppMyNewApp,
    .author = "Author Name",
    .version = "1.0",
    .github_repo = "author/my-new-app",
}

// In app_launcher.c (launch_community_app switch)
case CommunityAppMyNewApp:
    furi_log_info("APP", "My New App started");
    break;
```

## Installation

### Via Momentum Firmware

Most apps come pre-installed with Momentum Firmware. To update:

1. Visit [Momentum Web Updater](https://momentum-fw.dev/update)
2. Connect your Flipper Zero
3. Select latest version
4. Update

### Via qFlipper

1. Open qFlipper desktop app
2. Connect Flipper Zero
3. Navigate to File System
4. Copy app `.fap` files to `/apps/` directory
5. Restart device

### Community Apps

Many community apps require manual installation:

1. Download `.fap` file from GitHub
2. Copy to Flipper Zero via qFlipper
3. Navigate to Applications in Flipper menu
4. Launch installed app

## Resources

- **Momentum Firmware**: https://momentum-fw.dev/
- **Momentum Apps GitHub**: https://github.com/Next-Flip/Momentum-Apps
- **Community App Hub**: https://lab.flipper.net/apps/
- **Awesome Flipper**: https://github.com/123fzero/flipper-zero-awesome

## Troubleshooting

### App Won't Launch
- Ensure Momentum firmware is installed
- Check app compatibility with your firmware version
- Reinstall the app

### Missing Dependencies
- Some apps require additional libraries
- Check GitHub repo for dependencies
- Update Flipper firmware to latest version

### Performance Issues
- Close other running apps
- Restart your Flipper Zero
- Update to latest app version

## Legal Notice

All apps included in this firmware are for educational and authorized use only. Users are responsible for ensuring they comply with all applicable laws and regulations in their jurisdiction.
