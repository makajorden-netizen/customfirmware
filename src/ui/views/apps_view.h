#ifndef APPS_VIEW_H
#define APPS_VIEW_H

#include <gui/view.h>

typedef void (*AppsViewCallback)(const char* app_name);

View* apps_view_alloc(void);

void apps_view_free(View* view);

void apps_view_set_callback(View* view, AppsViewCallback callback);

#endif // APPS_VIEW_H