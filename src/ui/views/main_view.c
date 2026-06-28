#include "main_view.h"
#include "../ui.h"
#include <gui/elements.h>
#include <stdlib.h>

typedef struct {
    MainViewCallback callback;
    int selected;
} MainViewContext;

static void main_view_draw_callback(Canvas* canvas, void* model) {
    MainViewContext* ctx = (MainViewContext*)model;
    
    ui_draw_header(canvas, "Custom Firmware");
    
    const char* menu[] = {"Apps", "Settings", "System", "About"};
    int menu_count = 4;
    
    for(int i = 0; i < menu_count; i++) {
        int y = 30 + (i * 24);
        ui_draw_menu_item(canvas, 10, y, 108, 20, menu[i], i == ctx->selected);
    }
    
    ui_draw_footer(canvas, "UP/DOWN: Select | OK: Enter | BACK: Exit");
}

static bool main_view_input_callback(InputEvent* event, void* context) {
    MainViewContext* ctx = (MainViewContext*)context;
    
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
        case InputKeyOk:
            if(ctx->callback) ctx->callback();
            return true;
        default:
            return false;
    }
}

View* main_view_alloc(void) {
    View* view = view_alloc();
    MainViewContext* ctx = (MainViewContext*)malloc(sizeof(MainViewContext));
    
    ctx->selected = 0;
    ctx->callback = NULL;
    
    view_set_context(view, ctx);
    view_set_draw_callback(view, main_view_draw_callback);
    view_set_input_callback(view, main_view_input_callback);
    
    return view;
}

void main_view_free(View* view) {
    MainViewContext* ctx = (MainViewContext*)view_get_context(view);
    free(ctx);
    view_free(view);
}

void main_view_set_callback(View* view, MainViewCallback callback) {
    MainViewContext* ctx = (MainViewContext*)view_get_context(view);
    ctx->callback = callback;
}