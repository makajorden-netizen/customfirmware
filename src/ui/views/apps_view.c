#include "apps_view.h"
#include "../ui.h"
#include "../../apps/app_launcher.h"
#include <gui/elements.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    AppsViewCallback callback;
    int selected;
    int scroll_offset;
    bool show_momentum;
} AppsViewContext;

static void apps_view_draw_callback(Canvas* canvas, void* model) {
    AppsViewContext* ctx = (AppsViewContext*)model;
    
    ui_draw_header(canvas, ctx->show_momentum ? "Momentum Apps" : "Community Apps");
    
    canvas_set_color(canvas, ColorBlack);
    
    int app_count = ctx->show_momentum ? MOMENTUM_APPS_COUNT : COMMUNITY_APPS_COUNT;
    
    for(int i = 0; i < 3 && i < app_count; i++) {
        int app_index = ctx->scroll_offset + i;
        if(app_index >= app_count) break;
        
        int y = 30 + (i * 18);
        
        const char* app_name = NULL;
        if(ctx->show_momentum) {
            const MomentumApp* app = get_momentum_app(app_index);
            if(app) app_name = app->name;
        } else {
            const CommunityApp* app = get_community_app(app_index);
            if(app) app_name = app->name;
        }
        
        if(app_name == NULL) continue;
        
        if(app_index == ctx->selected) {
            canvas_draw_box(canvas, 5, y, 118, 16);
            canvas_set_color(canvas, ColorWhite);
        } else {
            canvas_set_color(canvas, ColorBlack);
        }
        
        canvas_draw_str(canvas, 10, y + 11, app_name);
        canvas_set_color(canvas, ColorBlack);
    }
    
    // Tab indicators
    canvas_draw_line(canvas, 0, 28, 128, 28);
    canvas_set_color(canvas, ColorBlack);
    canvas_draw_str(canvas, 5, 62, ctx->show_momentum ? "Momentum" : "Community");
}

static bool apps_view_input_callback(InputEvent* event, void* context) {
    AppsViewContext* ctx = (AppsViewContext*)context;
    
    if(event->type != InputTypePress) {
        return false;
    }
    
    int app_count = ctx->show_momentum ? MOMENTUM_APPS_COUNT : COMMUNITY_APPS_COUNT;
    
    switch(event->key) {
        case InputKeyUp:
            if(ctx->selected > 0) {
                ctx->selected--;
                if(ctx->selected < ctx->scroll_offset) {
                    ctx->scroll_offset = ctx->selected;
                }
            }
            return true;
        case InputKeyDown:
            if(ctx->selected < app_count - 1) {
                ctx->selected++;
                if(ctx->selected >= ctx->scroll_offset + 3) {
                    ctx->scroll_offset = ctx->selected - 2;
                }
            }
            return true;
        case InputKeyLeft:
        case InputKeyRight:
            // Switch between Momentum and Community apps
            ctx->show_momentum = !ctx->show_momentum;
            ctx->selected = 0;
            ctx->scroll_offset = 0;
            return true;
        case InputKeyOk:
            {
                const char* app_name = NULL;
                if(ctx->show_momentum) {
                    const MomentumApp* app = get_momentum_app(ctx->selected);
                    if(app) app_name = app->name;
                } else {
                    const CommunityApp* app = get_community_app(ctx->selected);
                    if(app) app_name = app->name;
                }
                
                if(app_name && ctx->callback) {
                    ctx->callback(app_name);
                }
            }
            return true;
        default:
            return false;
    }
}

View* apps_view_alloc(void) {
    View* view = view_alloc();
    AppsViewContext* ctx = (AppsViewContext*)malloc(sizeof(AppsViewContext));
    
    ctx->selected = 0;
    ctx->scroll_offset = 0;
    ctx->callback = NULL;
    ctx->show_momentum = true;
    
    view_set_context(view, ctx);
    view_set_draw_callback(view, apps_view_draw_callback);
    view_set_input_callback(view, apps_view_input_callback);
    
    return view;
}

void apps_view_free(View* view) {
    AppsViewContext* ctx = (AppsViewContext*)view_get_context(view);
    free(ctx);
    view_free(view);
}

void apps_view_set_callback(View* view, AppsViewCallback callback) {
    AppsViewContext* ctx = (AppsViewContext*)view_get_context(view);
    ctx->callback = callback;
}