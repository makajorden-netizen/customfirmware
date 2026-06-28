#ifndef SETTINGS_VIEW_H
#define SETTINGS_VIEW_H

#include <gui/view.h>

typedef void (*SettingsViewCallback)(void);

View* settings_view_alloc(void);

void settings_view_free(View* view);

void settings_view_set_callback(View* view, SettingsViewCallback callback);

#endif // SETTINGS_VIEW_H