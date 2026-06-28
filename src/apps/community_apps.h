#ifndef COMMUNITY_APPS_H
#define COMMUNITY_APPS_H

#include <furi.h>

/**
 * Popular Community Apps for Flipper Zero
 * Latest community-developed applications
 */

typedef enum {
    CommunityAppHabitFlow,
    CommunityAppStratagemHero,
    CommunityAppCellLab,
    CommunityAppFlipRogue,
    CommunityAppTriviaZero,
    CommunityAppSubGHZChat,
    CommunityAppVideoPlayer,
    CommunityAppCalculator,
    CommunityAppBadUSB,
    CommunityAppWifiJammer,
    CommunityAppDemoBoySimulator,
    CommunityAppClimateMonitor,
    CommunityAppCount,
} CommunityAppType;

typedef struct {
    const char* name;
    const char* description;
    CommunityAppType type;
    const char* author;
    const char* version;
    const char* github_repo;
} CommunityApp;

// Community apps registry
const CommunityApp community_apps[] = {
    {
        .name = "HabitFlow",
        .description = "Offline habit tracker with goals and streaks",
        .type = CommunityAppHabitFlow,
        .author = "Community",
        .version = "1.3",
        .github_repo = "flipper-zero/HabitFlow",
    },
    {
        .name = "Stratagem Hero",
        .description = "Helldivers 2-inspired tactical game",
        .type = CommunityAppStratagemHero,
        .author = "Community",
        .version = "2.1",
        .github_repo = "flipper-zero/stratagem-hero",
    },
    {
        .name = "Cell Lab",
        .description = "Tiny pixel world simulator",
        .type = CommunityAppCellLab,
        .author = "Community",
        .version = "1.5",
        .github_repo = "flipper-zero/cell-lab",
    },
    {
        .name = "FlipRogue",
        .description = "ASCII roguelike RPG adventure",
        .type = CommunityAppFlipRogue,
        .author = "Community",
        .version = "1.2",
        .github_repo = "flipper-zero/fliprogue",
    },
    {
        .name = "Trivia Zero",
        .description = "Bilingual flashcard trivia game",
        .type = CommunityAppTriviaZero,
        .author = "Community",
        .version = "1.4",
        .github_repo = "flipper-zero/trivia-zero",
    },
    {
        .name = "Sub-GHz Chat",
        .description = "Send text messages over Sub-GHz",
        .type = CommunityAppSubGHZChat,
        .author = "Community",
        .version = "1.6",
        .github_repo = "flipper-zero/subghz-chat",
    },
    {
        .name = "Video Player",
        .description = "Play video files on display",
        .type = CommunityAppVideoPlayer,
        .author = "Community",
        .version = "1.1",
        .github_repo = "flipper-zero/video-player",
    },
    {
        .name = "Calculator",
        .description = "Full-featured scientific calculator",
        .type = CommunityAppCalculator,
        .author = "Community",
        .version = "2.0",
        .github_repo = "flipper-zero/calculator",
    },
    {
        .name = "Bad USB",
        .description = "USB keyboard/mouse emulator",
        .type = CommunityAppBadUSB,
        .author = "Community",
        .version = "2.5",
        .github_repo = "flipper-zero/badusb",
    },
    {
        .name = "WiFi Jammer",
        .description = "Educational WiFi signal analyzer",
        .type = CommunityAppWifiJammer,
        .author = "Community",
        .version = "1.9",
        .github_repo = "flipper-zero/wifi-jammer",
    },
    {
        .name = "DemoBoy Simulator",
        .description = "Game Boy emulator",
        .type = CommunityAppDemoBoySimulator,
        .author = "Community",
        .version = "1.7",
        .github_repo = "flipper-zero/demoboy",
    },
    {
        .name = "Climate Monitor",
        .description = "Temperature and humidity monitor",
        .type = CommunityAppClimateMonitor,
        .author = "Community",
        .version = "1.0",
        .github_repo = "flipper-zero/climate-monitor",
    },
};

#define COMMUNITY_APPS_COUNT (sizeof(community_apps) / sizeof(community_apps[0]))

// App launcher function
void launch_community_app(CommunityAppType app_type);

// Get app by index
const CommunityApp* get_community_app(int index);

// Get app by name
const CommunityApp* find_community_app_by_name(const char* name);

#endif // COMMUNITY_APPS_H