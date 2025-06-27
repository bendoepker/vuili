#include "vuili.h"

/* Internal types and structures */
#include "internal.h"

/* Logging */
#include <log.h>

/* Memset, Strncpy */
#include <string.h>

/* Assert */
#include <assert.h>

VuiliData _VDATA = {0};

char VuiliErrorText[128] = {0};
static void __v_set_error_text(const char* const text, int n) {
    memset(VuiliErrorText, 0, 128);
    strncpy(VuiliErrorText, text, n);
}

static void __window_close_callback(GLFWwindow* data) {
    (void)data;
    _VDATA.window.should_close = true;
}

void V_InitWindow(const char* title, int pos_x, int pos_y, int width, int height) {
    _VDATA.window.position = (Size){ .x = pos_x, .y = pos_y };
    _VDATA.window.cur_size = (Size){ .x = width, .y = height };

    /* Initialize the GLFW Library */
    if(!glfwInit()) {
        /* GLFW Failed to Initialize, Panic! */
        //assert(1 && "Failed to initialize GLFW!!!");
        __v_set_error_text("Failed to initialize GLFW", 26);
        return;
    }

    _VDATA.window.window = glfwCreateWindow(width, height, title, NULL, NULL);
    _VDATA.window.should_close = false;
    glfwSetWindowPos(_VDATA.window.window, pos_x, pos_y);

    glfwSetWindowCloseCallback(_VDATA.window.window, __window_close_callback);
}

void V_CloseWindow() {
    if(_VDATA.window.window)
        glfwDestroyWindow(_VDATA.window.window);
    memset(&_VDATA, 0, sizeof(_VDATA));
    glfwTerminate();
}

void V_BeginDrawing() {
    //TODO:
    _VDATA.window.drawing = true;
}

void V_EndDrawing() {
    //TODO:
    _VDATA.window.drawing = false;
    glfwPollEvents();
}

void V_SwapBuffers() {
    assert(!_VDATA.window.drawing && "Cannot swap buffers while");
    glfwSwapBuffers(_VDATA.window.window);
}

const char* V_GetLastErrorText() {
    return VuiliErrorText;
}

void V_SetMinWindowSize(int width, int height) {
    _VDATA.window.min_size = (Size) { .x = width, .y = height };
    glfwSetWindowSizeLimits(_VDATA.window.window, width, height, GLFW_DONT_CARE, GLFW_DONT_CARE);
}

void V_SetMaxWindowSize(int width, int height) {
    _VDATA.window.max_size = (Size) { .x = width, .y = height };
    glfwSetWindowSizeLimits(_VDATA.window.window, GLFW_DONT_CARE, GLFW_DONT_CARE, width, height);
}

void V_ToggleFullscreen() {
    //TODO:
}

void V_ToggleWindowFlags(int flags) {
    _VDATA.window.flags ^= flags;
}

void V_SetWindowFramerate(int framerate) {
    //TODO:
}

// NOTE: This will toggle the flags in _VDATA then set it in GLFW
void V_ChangeWindowFlags(int flags) {
    V_ToggleWindowFlags(flags);
    //TODO: Set the flags in GLFW
}

bool V_WindowShouldClose() {
    return _VDATA.window.should_close;
}

V_Vec2 V_GetMousePositionAbsolute() {
    //TODO: This is going to be OS / Compositor specific
    return (V_Vec2) { 0, 0 };
}
