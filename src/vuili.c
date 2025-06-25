#include "vuili.h"
#include "config.h"
#include "internal.h"
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

VuiliData _VDATA = {0};

void V_InitWindow(const char* title, int pos_x, int pos_y, int width, int height) {
    _VDATA.window.position = (Size){ .x = pos_x, .y = pos_y };
    _VDATA.window.cur_size = (Size){ .x = width, .y = height };
}

void V_CloseWindow() {
    //TODO:
}

void V_ToggleWindowFlags(int flags) {
    _VDATA.window.flags ^= flags;
}

void V_SetWindowFramerate(int framerate) {
    return;
}

void V_ChangeWindowFlags(int flags) {
    return;
}

bool V_WindowShouldClose() {
    return true;
}
