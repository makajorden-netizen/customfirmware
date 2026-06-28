#include "ui.h"
#include <stdlib.h>
#include <string.h>
#include <furi.h>

static UIConfig* ui_config = NULL;

void ui_init(void) {
    if(ui_config == NULL) {
        ui_config = (UIConfig*)malloc(sizeof(UIConfig));
        
        ui_config->theme = UIThemeDark;
        ui_config->brightness = 255;
        ui_config->vibration_enabled = true;
        ui_config->sound_enabled = true;
        
        // Dark theme colors
        ui_config->colors.background = (UIColor){0, 0, 0};
        ui_config->colors.foreground = (UIColor){255, 255, 255};
        ui_config->colors.accent = (UIColor){0, 100, 200};
        ui_config->colors.highlight = (UIColor){255, 200, 0};
    }
}

void ui_deinit(void) {
    if(ui_config != NULL) {
        free(ui_config);
        ui_config = NULL;
    }
}

void ui_set_theme(UITheme theme) {
    if(ui_config == NULL) return;
    
    ui_config->theme = theme;
    
    if(theme == UIThemeLight) {
        ui_config->colors.background = (UIColor){255, 255, 255};
        ui_config->colors.foreground = (UIColor){0, 0, 0};
        ui_config->colors.accent = (UIColor){100, 150, 255};
        ui_config->colors.highlight = (UIColor){200, 100, 0};
    } else {
        ui_config->colors.background = (UIColor){0, 0, 0};
        ui_config->colors.foreground = (UIColor){255, 255, 255};
        ui_config->colors.accent = (UIColor){0, 100, 200};
        ui_config->colors.highlight = (UIColor){255, 200, 0};
    }
}

UIConfig* ui_get_config(void) {
    if(ui_config == NULL) {
        ui_init();
    }
    return ui_config;
}

void ui_draw_button(Canvas* canvas, int x, int y, int w, int h, const char* text, bool selected) {
    if(selected) {
        canvas_draw_box(canvas, x, y, w, h);
        canvas_set_color(canvas, ColorWhite);
    } else {
        canvas_draw_frame(canvas, x, y, w, h);
        canvas_set_color(canvas, ColorBlack);
    }
    
    canvas_draw_str_aligned(
        canvas, 
        x + w / 2, 
        y + h / 2, 
        AlignCenter, 
        AlignCenter, 
        text
    );
    
    canvas_set_color(canvas, ColorBlack);
}

void ui_draw_menu_item(Canvas* canvas, int x, int y, int w, int h, const char* text, bool selected) {
    if(selected) {
        canvas_draw_box(canvas, x, y, w, h);
        canvas_set_color(canvas, ColorWhite);
    } else {
        canvas_set_color(canvas, ColorBlack);
    }
    
    canvas_draw_str(canvas, x + 10, y + 12, text);
    canvas_set_color(canvas, ColorBlack);
}

void ui_draw_header(Canvas* canvas, const char* title) {
    canvas_draw_box(canvas, 0, 0, 128, 20);
    canvas_set_color(canvas, ColorWhite);
    canvas_draw_str_aligned(canvas, 64, 10, AlignCenter, AlignCenter, title);
    canvas_set_color(canvas, ColorBlack);
}

void ui_draw_footer(Canvas* canvas, const char* text) {
    canvas_draw_line(canvas, 0, 56, 128, 56);
    canvas_draw_str(canvas, 5, 62, text);
}