#include "app_launcher.h"
#include "momentum_apps.h"
#include "community_apps.h"
#include <stdlib.h>
#include <string.h>
#include <furi.h>

// Momentum Apps Implementation

void launch_momentum_app(MomentumAppType app_type) {
    const MomentumApp* app = NULL;
    
    for(int i = 0; i < MOMENTUM_APPS_COUNT; i++) {
        if(momentum_apps[i].type == app_type) {
            app = &momentum_apps[i];
            break;
        }
    }
    
    if(app == NULL) {
        furi_log_error("APP_LAUNCHER", "App not found: %d", app_type);
        return;
    }
    
    furi_log_info("APP_LAUNCHER", "Launching: %s v%s by %s", 
                  app->name, app->version, app->author);
    
    // App-specific launch logic
    switch(app_type) {
        case MomentumAppRFIDExplorer:
            furi_log_info("RFID", "RFID Explorer started");
            break;
        case MomentumAppNFCTools:
            furi_log_info("NFC", "NFC Tools started");
            break;
        case MomentumAppWeatherDecoder:
            furi_log_info("WEATHER", "Weather Decoder started");
            break;
        case MomentumAppIRRemote:
            furi_log_info("IR", "IR Remote started");
            break;
        case MomentumAppSubGHzScanner:
            furi_log_info("SUBGHZ", "Sub-GHz Scanner started");
            break;
        case MomentumAppBTFinder:
            furi_log_info("BT", "Bluetooth Finder started");
            break;
        case MomentumAppMusicPlayer:
            furi_log_info("MUSIC", "Music Player started");
            break;
        case MomentumAppFileManager:
            furi_log_info("FILE", "File Manager started");
            break;
        default:
            furi_log_error("APP_LAUNCHER", "Unknown app type");
            break;
    }
}

const MomentumApp* get_momentum_app(int index) {
    if(index < 0 || index >= MOMENTUM_APPS_COUNT) {
        return NULL;
    }
    return &momentum_apps[index];
}

const MomentumApp* find_momentum_app_by_name(const char* name) {
    if(name == NULL) {
        return NULL;
    }
    
    for(int i = 0; i < MOMENTUM_APPS_COUNT; i++) {
        if(strcmp(momentum_apps[i].name, name) == 0) {
            return &momentum_apps[i];
        }
    }
    return NULL;
}

// Community Apps Implementation

void launch_community_app(CommunityAppType app_type) {
    const CommunityApp* app = NULL;
    
    for(int i = 0; i < COMMUNITY_APPS_COUNT; i++) {
        if(community_apps[i].type == app_type) {
            app = &community_apps[i];
            break;
        }
    }
    
    if(app == NULL) {
        furi_log_error("APP_LAUNCHER", "App not found: %d", app_type);
        return;
    }
    
    furi_log_info("APP_LAUNCHER", "Launching: %s v%s by %s", 
                  app->name, app->version, app->author);
    furi_log_info("APP_LAUNCHER", "GitHub: %s", app->github_repo);
    
    // App-specific launch logic
    switch(app_type) {
        case CommunityAppHabitFlow:
            furi_log_info("HABIT", "HabitFlow started");
            break;
        case CommunityAppStratagemHero:
            furi_log_info("GAME", "Stratagem Hero started");
            break;
        case CommunityAppCellLab:
            furi_log_info("SIM", "Cell Lab started");
            break;
        case CommunityAppFlipRogue:
            furi_log_info("GAME", "FlipRogue started");
            break;
        case CommunityAppTriviaZero:
            furi_log_info("GAME", "Trivia Zero started");
            break;
        case CommunityAppSubGHZChat:
            furi_log_info("CHAT", "Sub-GHz Chat started");
            break;
        case CommunityAppVideoPlayer:
            furi_log_info("VIDEO", "Video Player started");
            break;
        case CommunityAppCalculator:
            furi_log_info("CALC", "Calculator started");
            break;
        case CommunityAppBadUSB:
            furi_log_info("USB", "Bad USB started");
            break;
        case CommunityAppWifiJammer:
            furi_log_info("WIFI", "WiFi Jammer started");
            break;
        case CommunityAppDemoBoySimulator:
            furi_log_info("EMU", "DemoBoy Simulator started");
            break;
        case CommunityAppClimateMonitor:
            furi_log_info("CLIMATE", "Climate Monitor started");
            break;
        default:
            furi_log_error("APP_LAUNCHER", "Unknown app type");
            break;
    }
}

const CommunityApp* get_community_app(int index) {
    if(index < 0 || index >= COMMUNITY_APPS_COUNT) {
        return NULL;
    }
    return &community_apps[index];
}

const CommunityApp* find_community_app_by_name(const char* name) {
    if(name == NULL) {
        return NULL;
    }
    
    for(int i = 0; i < COMMUNITY_APPS_COUNT; i++) {
        if(strcmp(community_apps[i].name, name) == 0) {
            return &community_apps[i];
        }
    }
    return NULL;
}