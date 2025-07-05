#include "vuili.h"

/* Internal types and structures */
/* Includes glfw and glad */
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

static void __window_close_callback(GLFWwindow* window) {
    (void)window;
    _VDATA.window.should_close = true;
}

static void __window_pos_callback(GLFWwindow* window, int x, int y) {
    (void)window;
    _VDATA.window.position.x = x;
    _VDATA.window.position.y = y;
}

static void __window_size_callback(GLFWwindow* window, int x, int y) {
    (void)window;
    _VDATA.window.size.x = x;
    _VDATA.window.size.y = y;
}

static void __frame_buffer_size_callback(GLFWwindow* window, int x, int y) {
    (void)window;
    glViewport(0, 0, x, y);
}

static void __glfw_error_callback(int error, const char* error_text) {
    PRINT("GLFW Error: code: %d, description: %s", error, error_text);
}

void VFP(InitWindow)(const char* title, int pos_x, int pos_y, int width, int height) {
    _VDATA.window.position = (Size){ .x = pos_x, .y = pos_y };
    _VDATA.window.size = (Size){ .x = width, .y = height };

    /* Initialize the GLFW Library */
    if(!glfwInit()) {
        /* GLFW Failed to Initialize, Panic! */
        //assert(1 && "Failed to initialize GLFW!!!");
        __v_set_error_text("Failed to initialize GLFW", 26);
        return;
    }
    glfwSetErrorCallback(__glfw_error_callback);

    /* GLFW OpenGL hints */
    /* NOTE: We are using our own generated Glad files so we can use 4.6 */
    glfwDefaultWindowHints();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    _VDATA.window.window = glfwCreateWindow(width, height, title, NULL, NULL);
    if(!_VDATA.window.window) {
        /* GLFW failed to create the window, abort the program */
        __v_set_error_text("GLFW failed to create a window", 31);
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(_VDATA.window.window); //Sync glfw to gl context
    _VDATA.window.should_close = false;
    glfwSetWindowPos(_VDATA.window.window, pos_x, pos_y);

    /* Load the GL library */
    int version_glad = gladLoadGL(glfwGetProcAddress);
    if(version_glad == 0) {
        /* Glad failed to load OpenGL*/
        __v_set_error_text("Glad failed to load OpenGL 4.6", 31);
        return;
    }
    PRINT("Loaded OpenGL version %i.%i", GLAD_VERSION_MAJOR(version_glad), GLAD_VERSION_MINOR(version_glad));

    /* Set GLFW callbacks */
    glfwSetWindowCloseCallback(_VDATA.window.window, __window_close_callback);
    glfwSetWindowPosCallback(_VDATA.window.window, __window_pos_callback);
    glfwSetWindowSizeCallback(_VDATA.window.window, __window_size_callback);
    glfwSetFramebufferSizeCallback(_VDATA.window.window, __frame_buffer_size_callback);

    /* Window defaults */
    _VDATA.window.background_color.a = 0xFF;
    glClearColor(_VDATA.window.background_color.r / 255.f,
                 _VDATA.window.background_color.g / 255.f,
                 _VDATA.window.background_color.b / 255.f,
                 _VDATA.window.background_color.a / 255.f);

#if (PLATFORM == WINDOWS) && defined(USE_HIGH_RES_TIMER)
    timeBeginPeriod(1);
#endif
}

void VFP(CloseWindow)() {
    if(_VDATA.window.window)
        glfwDestroyWindow(_VDATA.window.window);
    memset(&_VDATA, 0, sizeof(_VDATA));
    glfwTerminate();
#if (PLATFORM == WINDOWS) && defined(USE_HIGH_RES_TIMER)
    timeEndPeriod(1);
#endif
}

void VFP(ClearFrame)() {
    glClear(GL_COLOR_BUFFER_BIT);
}

void VFP(SetBackgroundColor)(VFP(Color) color) {
    _VDATA.window.background_color = color;
    glClearColor(_VDATA.window.background_color.r / 255.f,
                 _VDATA.window.background_color.g / 255.f,
                 _VDATA.window.background_color.b / 255.f,
                 _VDATA.window.background_color.a / 255.f
                 );
}

void VFP(BeginDrawing)() {
    _VDATA.window.drawing = true;

    /* Reset the frame timer */
    if(_VDATA.window.max_frame_time != 0)
        glfwSetTime(0);
}

void VFP(EndDrawing)() {
    _VDATA.window.drawing = false;
    glfwPollEvents();
    VFP(SwapFrameBuffers)();

    /* Partial busy sleep until next frame */
    if(_VDATA.window.max_frame_time != 0) {
        for(;;) {
            if(glfwGetTime() > _VDATA.window.max_frame_time)
                break;
            else Sleep(1); /* NOTE: USE_HIGH_RES_TIMER will increase this accuracy on windows */
        }
    }
}

void VFP(SwapFrameBuffers)() {
    glfwSwapBuffers(_VDATA.window.window);
}

void VFP(DrawFrame)() {
    /* Viewport Walking */
    //VFP(ClearFrame)();

    glfwPollEvents();

    /* Partial busy sleep until next frame */
    if(_VDATA.window.max_frame_time != 0) {
        for(;;) {
            if(glfwGetTime() > _VDATA.window.max_frame_time)
                break;
            else Sleep(1); /* NOTE: USE_HIGH_RES_TIMER will increase this accuracy on windows */
        }
    }
}

const char* VFP(GetLastErrorText)() {
    return VuiliErrorText;
}

void VFP(SetMinWindowSize)(int width, int height) {
    if(width <= 0 || height <= 0) {
        __v_set_error_text("Minimum size must be above 0", 29);
        return;
    }

    if(width > _VDATA.window.max_size.x || height > _VDATA.window.max_size.y) {
        __v_set_error_text("Minimum size cannot be greater than or equal to the maximum size", 65);
        return;
    }
    _VDATA.window.min_size = (Size) { .x = width, .y = height };
    int x = GLFW_DONT_CARE, y = GLFW_DONT_CARE;
    if(_VDATA.window.max_size.x) {
        //Max size is set, so it must be registered with glfw
        x = _VDATA.window.max_size.x;
        y = _VDATA.window.max_size.y;
    }
    glfwSetWindowSizeLimits(_VDATA.window.window, width, height, x, y);
}

void VFP(SetMaxWindowSize)(int width, int height) {
    if(width <= 0 || height <= 0) {
        __v_set_error_text("Maximum size must be above 0", 29);
        return;
    }

    if(width < _VDATA.window.min_size.x || height < _VDATA.window.max_size.y) {
        __v_set_error_text("Maximum size must be greater than or equal to the minimum size", 63);
    }
    _VDATA.window.max_size = (Size) { .x = width, .y = height };
    int x = GLFW_DONT_CARE, y = GLFW_DONT_CARE;
    if(_VDATA.window.min_size.x) {
        //Min size is set, so it must be registered with glfw
        x = _VDATA.window.min_size.x;
        y = _VDATA.window.min_size.y;
    }
    glfwSetWindowSizeLimits(_VDATA.window.window, x, y, width, height);
}

void VFP(UnsetMaxWindowSize)() {
    int x = GLFW_DONT_CARE, y = GLFW_DONT_CARE;
    if(_VDATA.window.min_size.x) {
        //Minimum size is set, don't disturb this
        x = _VDATA.window.min_size.x;
        y = _VDATA.window.min_size.y;
    }
    glfwSetWindowSizeLimits(_VDATA.window.window, x, y, GLFW_DONT_CARE, GLFW_DONT_CARE);
}

void VFP(UnsetMinWindowSize)() {
    int x = GLFW_DONT_CARE, y = GLFW_DONT_CARE;
    if(_VDATA.window.max_size.x) {
        //Maximum size is set, don't disturb this
        x = _VDATA.window.max_size.x;
        y = _VDATA.window.max_size.y;
    }
    glfwSetWindowSizeLimits(_VDATA.window.window, GLFW_DONT_CARE, GLFW_DONT_CARE, x, y);
}

void VFP(ToggleFullscreen)() {
    //TODO:
}

void VFP(ToggleWindowFlags)(int flags) {
    _VDATA.window.flags ^= flags;
}

void VFP(SetWindowFramerate)(int framerate) {
    if(framerate == 0)
        _VDATA.window.max_frame_time = 0;
    else
        _VDATA.window.max_frame_time = 1.f / framerate; /* Time in milliseconds */
}

// NOTE: This will toggle the flags in _VDATA then set it in GLFW
void VFP(ChangeWindowFlags)(int flags) {
    VFP(ToggleWindowFlags)(flags);
    //TODO: Set the flags in GLFW
}

void VFP(SetWindowTitle)(const char* title) {
    glfwSetWindowTitle(_VDATA.window.window, title);
}

bool VFP(WindowShouldClose)() {
    return _VDATA.window.should_close;
}

void VFP(SetWindowShouldClose)() {
    _VDATA.window.should_close = true;
}

VFP(Vec2) VFP(GetWindowPos)() {
    return (VFP(Vec2)) {
        .x = _VDATA.window.position.x,
        .y = _VDATA.window.position.y
    };
}

void VFP(SetWindowPosition)(int x, int y) {
    glfwSetWindowPos(_VDATA.window.window, x, y);
}

VFP(Vec2) VFP(GetWindowSize)() {
    return (VFP(Vec2)) {
        .x = _VDATA.window.size.x,
        .y = _VDATA.window.size.y
    };
}

void VFP(SetWindowSize)(int x, int y) {
    glfwSetWindowSize(_VDATA.window.window, x, y);
}

VFP(Vec2) VFP(GetMousePositionAbsolute)() {
    int x, y;
    double x1, y1;
    glfwGetWindowPos(_VDATA.window.window, &x, &y);
    glfwGetCursorPos(_VDATA.window.window, &x1, &y1);
    x1 += x;
    y1 += y;

    return (VFP(Vec2)) { .x = x1, .y = y1 };
}

VFP(Vec2) VFP(GetMousePosition)() {
    double x, y;
    glfwGetCursorPos(_VDATA.window.window, &x, &y);

    return (VFP(Vec2)){ .x = x, .y = y };
}
