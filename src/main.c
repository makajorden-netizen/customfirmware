#include <furi.h>
#include <gui/gui.h>
#include <gui/view_stack.h>
#include "ui/ui.h"
#include "ui/views/main_view.h"
#include "ui/views/settings_view.h"

typedef struct {
    Gui* gui;
    ViewStack* view_stack;
    View* main_view;
    View* settings_view;
} AppContext;

static AppContext* app_context = NULL;

static void app_init(void) {
    app_context = (AppContext*)malloc(sizeof(AppContext));
    
    // Initialize UI system
    ui_init();
    
    // Open GUI record
    app_context->gui = furi_record_open(RECORD_GUI);
    
    // Create view stack
    app_context->view_stack = view_stack_alloc();
    
    // Create views
    app_context->main_view = main_view_alloc();
    app_context->settings_view = settings_view_alloc();
    
    // Add views to stack
    view_stack_add_view(app_context->view_stack, app_context->main_view);
    view_stack_add_view(app_context->view_stack, app_context->settings_view);
    
    // Set main view as active
    view_stack_set_top(app_context->view_stack, app_context->main_view);
    
    // Add view stack to GUI
    gui_add_view_port(app_context->gui, view_stack_get_view(app_context->view_stack), GuiLayerFullscreen);
}

static void app_deinit(void) {
    if(app_context == NULL) return;
    
    gui_remove_view_port(app_context->gui, view_stack_get_view(app_context->view_stack));
    
    main_view_free(app_context->main_view);
    settings_view_free(app_context->settings_view);
    view_stack_free(app_context->view_stack);
    
    furi_record_close(RECORD_GUI);
    
    ui_deinit();
    
    free(app_context);
    app_context = NULL;
}

int32_t main(void) {
    app_init();
    
    // Application runs until GUI handles shutdown
    furi_thread_yield();
    
    app_deinit();
    
    return 0;
}