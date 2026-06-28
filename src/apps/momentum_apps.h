#ifndef MOMENTUM_APPS_H
#define MOMENTUM_APPS_H

#include <furi.h>

/**
 * Momentum Firmware Apps Integration
 * Latest Momentum apps and features for Flipper Zero
 */

typedef enum {
    MomentumAppRFIDExplorer,
    MomentumAppNFCTools,
    MomentumAppWeatherDecoder,
    MomentumAppIRRemote,
    MomentumAppSubGHzScanner,
    MomentumAppBTFinder,
    MomentumAppMusicPlayer,
    MomentumAppFileManager,
    MomentumAppCount,
} MomentumAppType;

typedef struct {
    const char* name;
    const char* description;
    MomentumAppType type;
    const char* author;
    const char* version;
} MomentumApp;

// App registry
const MomentumApp momentum_apps[] = {
    {
        .name = "RFID Explorer",
        .description = "Explore and detect RFID tags",
        .type = MomentumAppRFIDExplorer,
        .author = "Momentum Team",
        .version = "2.1",
    },
    {
        .name = "NFC Tools",
        .description = "Read/write NFC tags and automate",
        .type = MomentumAppNFCTools,
        .author = "Momentum Team",
        .version = "2.0",
    },
    {
        .name = "Weather Decoder",
        .description = "Decode weather station signals",
        .type = MomentumAppWeatherDecoder,
        .author = "Momentum Team",
        .version = "1.5",
    },
    {
        .name = "IR Remote",
        .description = "Infrared remote control emulator",
        .type = MomentumAppIRRemote,
        .author = "Momentum Team",
        .version = "2.2",
    },
    {
        .name = "Sub-GHz Scanner",
        .description = "Advanced Sub-GHz signal scanning",
        .type = MomentumAppSubGHzScanner,
        .author = "Momentum Team",
        .version = "2.3",
    },
    {
        .name = "Bluetooth Finder",
        .description = "Identify nearby Bluetooth devices",
        .type = MomentumAppBTFinder,
        .author = "Momentum Team",
        .version = "1.8",
    },
    {
        .name = "Music Player",
        .description = "Play tunes on your Flipper",
        .type = MomentumAppMusicPlayer,
        .author = "Momentum Team",
        .version = "1.2",
    },
    {
        .name = "File Manager",
        .description = "Advanced file navigation and transfer",
        .type = MomentumAppFileManager,
        .author = "Momentum Team",
        .version = "2.4",
    },
};

#define MOMENTUM_APPS_COUNT (sizeof(momentum_apps) / sizeof(momentum_apps[0]))

// App launcher function
void launch_momentum_app(MomentumAppType app_type);

// Get app by index
const MomentumApp* get_momentum_app(int index);

// Get app by name
const MomentumApp* find_momentum_app_by_name(const char* name);

#endif // MOMENTUM_APPS_H