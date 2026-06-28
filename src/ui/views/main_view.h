#ifndef MAIN_VIEW_H
#define MAIN_VIEW_H

#include <gui/view.h>

typedef void (*MainViewCallback)(void);

View* main_view_alloc(void);

void main_view_free(View* view);

void main_view_set_callback(View* view, MainViewCallback callback);

#endif // MAIN_VIEW_H