/**
 * Theme Management Example
 * Shows how to use and switch themes
 */

#include <furi.h>
#include "../src/ui/ui.h"

void theme_example(void) {
    // Initialize UI system
    ui_init();
    
    // Get current configuration
    UIConfig* config = ui_get_config();
    
    // Print current theme
    const char* theme_name = (config->theme == UIThemeDark) ? "Dark" : "Light";
    furi_log_info("THEME", "Current theme: %s", theme_name);
    
    // Switch to light theme
    furi_log_info("THEME", "Switching to light theme...");
    ui_set_theme(UIThemeLight);
    
    config = ui_get_config();
    furi_log_info("THEME", "Background: RGB(%d, %d, %d)", 
                  config->colors.background.r,
                  config->colors.background.g,
                  config->colors.background.b);
    furi_log_info("THEME", "Foreground: RGB(%d, %d, %d)", 
                  config->colors.foreground.r,
                  config->colors.foreground.g,
                  config->colors.foreground.b);
    
    // Adjust settings
    config->brightness = 128;
    config->vibration_enabled = true;
    config->sound_enabled = false;
    
    furi_log_info("THEME", "Brightness set to: %d", config->brightness);
    furi_log_info("THEME", "Vibration: %s", 
                  config->vibration_enabled ? "enabled" : "disabled");
    furi_log_info("THEME", "Sound: %s", 
                  config->sound_enabled ? "enabled" : "disabled");
    
    // Switch back to dark theme
    ui_set_theme(UIThemeDark);
    
    furi_log_info("THEME", "Theme example complete");
    
    // Cleanup
    ui_deinit();
}
