#ifndef CUSTOM_UI_H
#define CUSTOM_UI_H

#include <gui/gui.h>
#include <gui/canvas.h>
#include <input/input.h>

typedef enum {
    UIThemeLight,
    UIThemeDark,
} UITheme;

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} UIColor;

typedef struct {
    UIColor background;
    UIColor foreground;
    UIColor accent;
    UIColor highlight;
} UIColorScheme;

typedef struct {
    UITheme theme;
    UIColorScheme colors;
    uint8_t brightness;
    bool vibration_enabled;
    bool sound_enabled;
} UIConfig;

// Initialize UI system
void ui_init(void);

// Cleanup UI system
void ui_deinit(void);

// Set theme
void ui_set_theme(UITheme theme);

// Get current config
UIConfig* ui_get_config(void);

// Draw utilities
void ui_draw_button(Canvas* canvas, int x, int y, int w, int h, const char* text, bool selected);
void ui_draw_menu_item(Canvas* canvas, int x, int y, int w, int h, const char* text, bool selected);
void ui_draw_header(Canvas* canvas, const char* title);
void ui_draw_footer(Canvas* canvas, const char* text);

#endif // CUSTOM_UI_H