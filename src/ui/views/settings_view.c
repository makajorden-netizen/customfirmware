#include "settings_view.h"
#include "../ui.h"
#include <gui/elements.h>
#include <stdlib.h>

typedef struct {
    SettingsViewCallback callback;
    int selected;
    UIConfig* config;
} SettingsViewContext;

static void settings_view_draw_callback(Canvas* canvas, void* model) {
    SettingsViewContext* ctx = (SettingsViewContext*)model;
    
    ui_draw_header(canvas, "Settings");
    
    canvas_set_color(canvas, ColorBlack);
    
    // Brightness setting
    int y = 30;
    if(ctx->selected == 0) {
        canvas_draw_box(canvas, 10, y, 108, 18);
        canvas_set_color(canvas, ColorWhite);
    }
    canvas_draw_str(canvas, 15, y + 12, "Brightness");
    canvas_set_color(canvas, ColorBlack);
    
    // Theme setting
    y += 24;
    if(ctx->selected == 1) {
        canvas_draw_box(canvas, 10, y, 108, 18);
        canvas_set_color(canvas, ColorWhite);
    }
    canvas_draw_str(canvas, 15, y + 12, "Theme");
    canvas_set_color(canvas, ColorBlack);
    
    // Sound setting
    y += 24;
    if(ctx->selected == 2) {
        canvas_draw_box(canvas, 10, y, 108, 18);
        canvas_set_color(canvas, ColorWhite);
    }
    canvas_draw_str(canvas, 15, y + 12, "Sound");
    canvas_set_color(canvas, ColorBlack);
    
    // Vibration setting
    y += 24;
    if(ctx->selected == 3) {
        canvas_draw_box(canvas, 10, y, 108, 18);
        canvas_set_color(canvas, ColorWhite);
    }
    canvas_draw_str(canvas, 15, y + 12, "Vibration");
    canvas_set_color(canvas, ColorBlack);
}

static bool settings_view_input_callback(InputEvent* event, void* context) {
    SettingsViewContext* ctx = (SettingsViewContext*)context;
    
    if(event->type != InputTypePress) {
        return false;
    }
    
    switch(event->key) {
        case InputKeyUp:
            if(ctx->selected > 0) ctx->selected--;
            return true;
        case InputKeyDown:
            if(ctx->selected < 3) ctx->selected++;
            return true;
        case InputKeyLeft:
        case InputKeyRight:
            // Toggle settings
            return true;
        default:
            return false;
    }
}

View* settings_view_alloc(void) {
    View* view = view_alloc();
    SettingsViewContext* ctx = (SettingsViewContext*)malloc(sizeof(SettingsViewContext));
    
    ctx->selected = 0;
    ctx->callback = NULL;
    ctx->config = ui_get_config();
    
    view_set_context(view, ctx);
    view_set_draw_callback(view, settings_view_draw_callback);
    view_set_input_callback(view, settings_view_input_callback);
    
    return view;
}

void settings_view_free(View* view) {
    SettingsViewContext* ctx = (SettingsViewContext*)view_get_context(view);
    free(ctx);
    view_free(view);
}

void settings_view_set_callback(View* view, SettingsViewCallback callback) {
    SettingsViewContext* ctx = (SettingsViewContext*)view_get_context(view);
    ctx->callback = callback;
}