/**
 * Simple Application Example
 * Demonstrates basic UI usage
 */

#include <furi.h>
#include <gui/gui.h>
#include "../src/ui/ui.h"
#include "../src/ui/views/main_view.h"

typedef struct {
    Gui* gui;
    View* main_view;
} SimpleApp;

static void render_custom(Canvas* canvas, void* context) {
    SimpleApp* app = (SimpleApp*)context;
    
    ui_draw_header(canvas, "Simple App");
    
    canvas_set_color(canvas, ColorBlack);
    canvas_draw_str_aligned(canvas, 64, 40, AlignCenter, AlignCenter, 
                            "Hello, Flipper Zero!");
    
    ui_draw_footer(canvas, "BACK: Exit");
}

static bool input_callback(InputEvent* event, void* context) {
    SimpleApp* app = (SimpleApp*)context;
    
    if(event->type != InputTypePress) {
        return false;
    }
    
    switch(event->key) {
        case InputKeyBack:
            // Exit application
            furi_thread_flags_set(furi_thread_get_current_id(), 1);
            return true;
        default:
            return false;
    }
}

int32_t simple_app(void) {
    // Initialize UI
    ui_init();
    
    SimpleApp app;
    app.gui = furi_record_open(RECORD_GUI);
    
    ViewPort* view_port = view_port_alloc();
    view_port_draw_callback_set(view_port, render_custom, &app);
    view_port_input_callback_set(view_port, input_callback, &app);
    
    gui_add_view_port(app.gui, view_port, GuiLayerFullscreen);
    
    // Wait for exit signal
    furi_thread_flags_wait(1, FuriWaitForever);
    
    gui_remove_view_port(app.gui, view_port);
    view_port_free(view_port);
    furi_record_close(RECORD_GUI);
    
    ui_deinit();
    
    return 0;
}
