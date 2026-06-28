#include <furi.h>
#include <gui/gui.h>
#include <gui/elements.h>
#include <gui/canvas.h>
#include <input/input.h>

typedef enum {
    ViewMain,
    ViewSettings,
    ViewApps,
    ViewAbout,
} ViewType;

typedef struct {
    ViewType current_view;
    int selected_item;
    int scroll_offset;
} UIState;

static void draw_main_view(Canvas* canvas, UIState* state) {
    canvas_clear(canvas);
    canvas_set_color(canvas, ColorBlack);
    
    // Header
    canvas_draw_box(canvas, 0, 0, 128, 20);
    canvas_set_color(canvas, ColorWhite);
    canvas_draw_str_aligned(canvas, 64, 10, AlignCenter, AlignCenter, "Custom Firmware");
    
    // Menu items
    canvas_set_color(canvas, ColorBlack);
    const char* menu_items[] = {"Apps", "Settings", "About", "Reboot"};
    int menu_count = 4;
    
    for(int i = 0; i < menu_count; i++) {
        int y = 30 + (i * 25);
        
        if(i == state->selected_item) {
            canvas_draw_box(canvas, 5, y, 118, 20);
            canvas_set_color(canvas, ColorWhite);
        } else {
            canvas_set_color(canvas, ColorBlack);
        }
        
        canvas_draw_str_aligned(canvas, 64, y + 10, AlignCenter, AlignCenter, menu_items[i]);
        canvas_set_color(canvas, ColorBlack);
    }
}

static void draw_settings_view(Canvas* canvas, UIState* state) {
    canvas_clear(canvas);
    canvas_set_color(canvas, ColorBlack);
    
    // Header
    canvas_draw_box(canvas, 0, 0, 128, 20);
    canvas_set_color(canvas, ColorWhite);
    canvas_draw_str_aligned(canvas, 64, 10, AlignCenter, AlignCenter, "Settings");
    
    // Settings options
    canvas_set_color(canvas, ColorBlack);
    const char* settings[] = {"Display", "Sound", "Vibration", "Back"};
    int settings_count = 4;
    
    for(int i = 0; i < settings_count; i++) {
        int y = 30 + (i * 20);
        
        if(i == state->selected_item) {
            canvas_draw_box(canvas, 5, y, 118, 18);
            canvas_set_color(canvas, ColorWhite);
        } else {
            canvas_set_color(canvas, ColorBlack);
        }
        
        canvas_draw_str(canvas, 15, y + 12, settings[i]);
        canvas_set_color(canvas, ColorBlack);
    }
}

static void draw_apps_view(Canvas* canvas, UIState* state) {
    canvas_clear(canvas);
    canvas_set_color(canvas, ColorBlack);
    
    // Header
    canvas_draw_box(canvas, 0, 0, 128, 20);
    canvas_set_color(canvas, ColorWhite);
    canvas_draw_str_aligned(canvas, 64, 10, AlignCenter, AlignCenter, "Applications");
    
    // App list
    canvas_set_color(canvas, ColorBlack);
    const char* apps[] = {"WiFi Scanner", "Sub-GHz", "NFC Reader", "GPIO", "Back"};
    int app_count = 5;
    
    for(int i = 0; i < app_count; i++) {
        int y = 30 + (i * 18);
        
        if(i == state->selected_item) {
            canvas_draw_box(canvas, 5, y, 118, 16);
            canvas_set_color(canvas, ColorWhite);
        } else {
            canvas_set_color(canvas, ColorBlack);
        }
        
        canvas_draw_str(canvas, 15, y + 11, apps[i]);
        canvas_set_color(canvas, ColorBlack);
    }
}

static void draw_about_view(Canvas* canvas, UIState* state) {
    canvas_clear(canvas);
    canvas_set_color(canvas, ColorBlack);
    
    // Header
    canvas_draw_box(canvas, 0, 0, 128, 20);
    canvas_set_color(canvas, ColorWhite);
    canvas_draw_str_aligned(canvas, 64, 10, AlignCenter, AlignCenter, "About");
    
    // About info
    canvas_set_color(canvas, ColorBlack);
    canvas_draw_str_aligned(canvas, 64, 35, AlignCenter, AlignCenter, "Custom Firmware");
    canvas_draw_str_aligned(canvas, 64, 50, AlignCenter, AlignCenter, "Version: 1.0.0");
    canvas_draw_str_aligned(canvas, 64, 65, AlignCenter, AlignCenter, "Back");
    
    if(state->selected_item == 0) {
        canvas_draw_box(canvas, 40, 62, 48, 14);
        canvas_set_color(canvas, ColorWhite);
        canvas_draw_str_aligned(canvas, 64, 69, AlignCenter, AlignCenter, "Back");
    }
}

static void render_callback(Canvas* canvas, void* ctx) {
    UIState* state = (UIState*)ctx;
    
    switch(state->current_view) {
        case ViewMain:
            draw_main_view(canvas, state);
            break;
        case ViewSettings:
            draw_settings_view(canvas, state);
            break;
        case ViewApps:
            draw_apps_view(canvas, state);
            break;
        case ViewAbout:
            draw_about_view(canvas, state);
            break;
    }
}

static void input_callback(InputEvent* input_event, void* ctx) {
    FuriMessageQueue* queue = (FuriMessageQueue*)ctx;
    furi_message_queue_put(queue, input_event, FuriWaitForever);
}

int32_t ui_main(void) {
    UIState state = {
        .current_view = ViewMain,
        .selected_item = 0,
        .scroll_offset = 0,
    };
    
    Gui* gui = furi_record_open(RECORD_GUI);
    ViewPort* view_port = view_port_alloc();
    view_port_draw_callback_set(view_port, render_callback, &state);
    
    FuriMessageQueue* input_queue = furi_message_queue_alloc(32, sizeof(InputEvent));
    view_port_input_callback_set(view_port, input_callback, input_queue);
    
    gui_add_view_port(gui, view_port, GuiLayerFullscreen);
    
    InputEvent input_event;
    bool running = true;
    
    while(running) {
        if(furi_message_queue_get(input_queue, &input_event, FuriWaitForever) == FuriStatusOk) {
            if(input_event.type == InputTypePress) {
                switch(input_event.key) {
                    case InputKeyUp:
                        if(state.selected_item > 0) {
                            state.selected_item--;
                        }
                        break;
                    case InputKeyDown:
                        state.selected_item++;
                        break;
                    case InputKeyOk:
                        // Handle selection based on current view
                        break;
                    case InputKeyBack:
                        if(state.current_view == ViewMain) {
                            running = false;
                        } else {
                            state.current_view = ViewMain;
                            state.selected_item = 0;
                        }
                        break;
                    default:
                        break;
                }
            }
            view_port_update(view_port);
        }
    }
    
    gui_remove_view_port(gui, view_port);
    view_port_free(view_port);
    furi_message_queue_free(input_queue);
    furi_record_close(RECORD_GUI);
    
    return 0;
}