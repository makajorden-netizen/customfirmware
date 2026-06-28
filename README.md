# customfirmware
FlipperZero Custom Firmware - Advanced UI System

## Overview
A complete custom UI framework for Flipper Zero firmware with modular view system, configurable themes, and intuitive navigation.

## Features
- **Modern UI System**: Custom-built interface with consistent styling
- **Modular View Architecture**: Separate view components (Main, Settings, Apps, System)
- **Theme Support**: Light and dark themes with customizable colors
- **Settings Management**: Brightness, sound, vibration, and theme controls
- **Navigation Stack**: Stack-based view navigation for intuitive flow

## Architecture

### Core Components
- `src/ui/ui.c|h` - UI configuration and drawing utilities
- `src/ui/main.c` - Main UI renderer
- `src/ui/views/` - Individual view implementations

### Views
- **Main View**: Menu-driven primary interface
- **Settings View**: System configuration options
- **Apps View**: Application launcher (expandable)
- **System View**: System information and controls

## Build
```bash
mkdir build
cd build
cmake ..
make
```

## Usage
The firmware initializes with a main menu providing access to:
- Applications
- Settings
- System information
- About

## Navigation
- **UP/DOWN**: Navigate menu items
- **OK**: Select menu item
- **LEFT/RIGHT**: Adjust settings
- **BACK**: Return to main menu / Exit

## Extensibility
Add new views by:
1. Creating `src/ui/views/new_view.h` and `src/ui/views/new_view.c`
2. Implementing `view_alloc()`, `view_free()`, and callbacks
3. Registering in view stack in `src/main.c`

## Configuration
UI theme and settings are managed through `UIConfig` structure in `src/ui/ui.h`.
Default theme: Dark mode with system colors.