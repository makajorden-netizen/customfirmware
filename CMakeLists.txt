cmake_minimum_required(VERSION 3.22)

project(customfirmware C)

set(CMAKE_C_STANDARD 11)

# UI sources
set(UI_SOURCES
    src/ui/ui.c
    src/ui/main.c
    src/ui/views/main_view.c
    src/ui/views/settings_view.c
)

add_library(customfirmware_ui ${UI_SOURCES})

target_include_directories(customfirmware_ui PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Main application
add_executable(customfirmware_app src/main.c)

target_link_libraries(customfirmware_app customfirmware_ui)