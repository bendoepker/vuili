#include "vuili.h"

/* Internal types and structures */
/* Includes glfw and glad */
#include "internal.h"

/* Logging */
#include <log.h>

/* Memset, Strncpy, sprintf, strlen */
#include <string.h>
#include <stdio.h>

/* Assert */
#include <assert.h>

/* For malloc / calloc / realloc */
#include <stdlib.h>

VuiliData _VDATA = {0};

void VFP(SleepX)(int milli) {
    Sleep(milli);
}

/* Global Error Text */
char VuiliErrorText[128] = {0};

/* Internal function declarations */
static VFP(Viewport)* __get_viewport_pointer(VFP(ViewportID) id);
static int __get_viewport_index(VFP(ViewportID) id);
void _ExecuteDrawCommands(VFP(Viewport)* viewport);

/* Internal Callbacks */
static void __v_set_error_text(const char* const text, int n) {
    memset(VuiliErrorText, 0, 128);
    strncpy(VuiliErrorText, text, n);
}

static void __window_close_callback(GLFWwindow* window) {
    (void)window;
    _VDATA.window.should_close = true;
}

static void __window_pos_callback(GLFWwindow* window, int x, int y) {
    if(glfwGetWindowMonitor(window))
        return;
    _VDATA.window.position.x = x;
    _VDATA.window.position.y = y;
}

static void __window_size_callback(GLFWwindow* window, int x, int y) {
    if(glfwGetWindowMonitor(window))
        return;
    _VDATA.window.size.x = x;
    _VDATA.window.size.y = y;
}

static void __minimize_callback(GLFWwindow* window, int minimized) {
    (void)window;
    if(minimized)
        _VDATA.window.minimized = true;
    else
        _VDATA.window.minimized = false;
}

static void __maximize_callback(GLFWwindow* window, int maximized) {
    (void)window;
    if(maximized)
        _VDATA.window.maximized = true;
    else
        _VDATA.window.maximized = false;
}

static void __frame_buffer_size_callback(GLFWwindow* window, int x, int y) {
    (void)window;
    int width, height;
    glfwGetFramebufferSize(_VDATA.window.window, &width, &height);
    glViewport(0, 0, width, height);
}

static void __glfw_error_callback(int error, const char* error_text) {
    PRINT("GLFW Error: code: %d, description: %s", error, error_text);
}

static void __key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if(key == _VDATA.input.fullscreen_key) {
        if(action == GLFW_PRESS) {
            ToggleFullscreen();
            return;
        }
    }
}

static void __mouse_callback(GLFWwindow* window, int button, int action, int mods) {
    (void)window;
}

void VFP(InitWindow)(const char* title, int pos_x, int pos_y, int width, int height) {
    _VDATA.window.position = (Size){ .x = pos_x, .y = pos_y };
    _VDATA.window.size = (Size){ .x = width, .y = height };

    /* Initialize the GLFW Library */
    if(!glfwInit()) {
        /* GLFW Failed to Initialize, Panic! */
        //assert(0 && "Failed to initialize GLFW!!!");
        __v_set_error_text("Failed to initialize GLFW", 26);
        return;
    }
    glfwSetErrorCallback(__glfw_error_callback);

    /* GLFW / OpenGL hints */
    /* NOTE: We are using our own generated Glad files so we can use 4.6 */
    glfwDefaultWindowHints();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* SECTION: Apply window creation flags */
    /* These must be toggled before the window creation and has no effect otherwise */
    if(_VDATA.window.flags & WINDOW_RESIZABLE) {
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    } else {
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    }

    if(_VDATA.window.flags & WINDOW_UNFOCUSED) {
        glfwWindowHint(GLFW_FOCUSED, GLFW_FALSE);
    } else {
        glfwWindowHint(GLFW_FOCUSED, GLFW_TRUE);
    }

    if(_VDATA.window.flags & TRANSPARENT_CLIENT) {
        glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
    }

    if(_VDATA.window.flags & CUSTOM_TITLEBAR) {
        assert(0 && "TODO: CUSTOM_TITLEBAR flag needs implemented");
        //TODO:
        glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
    }

    if(_VDATA.window.flags & WINDOW_MAXIMIZED) {
        glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);
    }

    glfwWindowHint(GLFW_POSITION_X, pos_x);
    glfwWindowHint(GLFW_POSITION_Y, pos_y);

    if(_VDATA.input.fullscreen_key == VFP(KEY_NONE))
        _VDATA.input.fullscreen_key = VFP(KEY_F11);

    /* SECTION: Window Creation */
    _VDATA.window.window = glfwCreateWindow(width, height, title, NULL, NULL);
    if(!_VDATA.window.window) {
        /* GLFW failed to create the window, abort the program */
        __v_set_error_text("GLFW failed to create a window", 31);
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(_VDATA.window.window); //Sync glfw to gl context
    _VDATA.window.should_close = false;

    /* Window flags that must be applied after window creation... */
    if(_VDATA.window.flags & WINDOW_FULLSCREEN) {
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        glfwSetWindowMonitor(_VDATA.window.window, monitor, 0, 0, mode->width, mode->height, GLFW_DONT_CARE);
        _VDATA.window.fullscreen = true;
    }

    if(_VDATA.window.flags & WINDOW_MINIMIZED) {
        glfwIconifyWindow(_VDATA.window.window);
    }

    /* Load the GL library */
    int version_glad = gladLoadGL(glfwGetProcAddress);
    if(version_glad == 0) {
        /* Glad failed to load OpenGL*/
        __v_set_error_text("Glad failed to load OpenGL 4.6", 31);
        return;
    }

    /* Set GLFW callbacks */
    glfwSetWindowCloseCallback(_VDATA.window.window, __window_close_callback);
    glfwSetWindowPosCallback(_VDATA.window.window, __window_pos_callback);
    glfwSetWindowSizeCallback(_VDATA.window.window, __window_size_callback);
    glfwSetFramebufferSizeCallback(_VDATA.window.window, __frame_buffer_size_callback);
    glfwSetWindowMaximizeCallback(_VDATA.window.window, __maximize_callback);
    glfwSetWindowIconifyCallback(_VDATA.window.window, __minimize_callback);
    glfwSetKeyCallback(_VDATA.window.window, __key_callback);
    glfwSetMouseButtonCallback(_VDATA.window.window, __mouse_callback);

    /* Window defaults */
    _VDATA.window.background_color.a = 0xFF;
    glViewport(0, 0, width, height);
    glClearColor(_VDATA.window.background_color.r / 255.f,
                 _VDATA.window.background_color.g / 255.f,
                 _VDATA.window.background_color.b / 255.f,
                 _VDATA.window.background_color.a / 255.f);

#if defined(_WIN32) && defined(USE_HIGH_RES_TIMER)
    timeBeginPeriod(1);

    TIMECAPS tc = {0};
    timeGetDevCaps(&tc, sizeof(tc));
    _VDATA.window.timer_resolution = tc.wPeriodMin / 1000.;
#endif

    /* Set the main window viewport */
    VFP(ViewportID) viewport_id = RegisterViewport(STATIC_VIEWPORT, -1, (VFP(Rectangle)) {.x = 0, .y = 0, .width = width, .height = height });
    if(viewport_id != 0) {
        /* NOTE: I don't like this being the case but for now it will have to do */
        /* TODO: ^ */
        __v_set_error_text("Viewports must be registered after the window creation", 55);
        glfwDestroyWindow(_VDATA.window.window);
        glfwTerminate();
        return;
    }

    __v_set_error_text("", 1);
}

void VFP(CloseWindow)() {
    if(_VDATA.window.window)
        glfwDestroyWindow(_VDATA.window.window);
    for(int i = 0; i < _VDATA.num_viewports; i++) {
        free(_VDATA.viewports[i]);
    }
    memset(&_VDATA, 0, sizeof(_VDATA));
    glfwTerminate();
#if defined(_WIN32) && defined(USE_HIGH_RES_TIMER)
    timeEndPeriod(1);
#endif
}

void VFP(ClearFrame)() {
    glClearColor(_VDATA.window.background_color.r / 255.f,
                 _VDATA.window.background_color.g / 255.f,
                 _VDATA.window.background_color.b / 255.f,
                 _VDATA.window.background_color.a / 255.f
                 );
    glClear(GL_COLOR_BUFFER_BIT);
}

void VFP(SetBackgroundColor)(VFP(Color) color) {
    _VDATA.window.background_color = color;
}

void VFP(BeginDrawing)() {
    _VDATA.window.drawing = true;

    /* Reset the frame timer */
    if(_VDATA.window.min_frame_time != 0)
        glfwSetTime(0);
}

void VFP(EndDrawing)() {
    _VDATA.window.drawing = false;
    glfwPollEvents();
    VFP(SwapFrameBuffers)();

    /* Partial busy sleep until next frame */
    if(_VDATA.window.min_frame_time != 0) {
        for(;;) {
            if(glfwGetTime() > _VDATA.window.min_frame_time)
                break;
            else Sleep(1); /* NOTE: USE_HIGH_RES_TIMER will increase this accuracy on windows */
        }
    }
}

void VFP(SwapFrameBuffers)() {
    glfwSwapBuffers(_VDATA.window.window);
}

void VFP(PollEvents)() {
    glfwPollEvents();
}

void VFP(DrawFrame)() {

    /* Frame Drawing */
    VFP(ClearFrame)();
    VFP(ViewportID) draw_layer[MAX_VIEWPORTS] = {0};
    VFP(ViewportID) prev_draw_layer[MAX_VIEWPORTS] = {0};
    /* Generate first draw layer */
    for(int i = 0; i < MAX_CHILD_VIEWPORTS; i++) {
        if(_VDATA.viewports[0]->children[i] == 0)
            break;
        else
            draw_layer[i] = _VDATA.viewports[0]->children[i];
    }
    for(int i = 0;; i++) {
        /* Each viewport needs to be draw from parent viewport to child viewport, layer by layer */
        /*
        *           *       < Draw this
        *         *   *     < Then these
        *        * * * *    < Then these
        *
        *   Execute draw commands for each viewport in draw layer
        *   Move draw layer to prev draw layer
        *   Generate next draw layer
        */

        _ExecuteDrawCommands(__get_viewport_pointer(draw_layer[i]));

    }

    VFP(SwapFrameBuffers)();

    /* Partial busy sleep until next frame */
    if(_VDATA.window.min_frame_time != 0) {
        for(;;) {
            if(glfwGetTime() + _VDATA.window.timer_resolution > _VDATA.window.min_frame_time)
                break;
            else Sleep(1); /* NOTE: USE_HIGH_RES_TIMER will increase this accuracy on windows */
        }
    }
    /* Input handling */
    VFP(PollEvents)();
    _VDATA.window.last_frame_time = glfwGetTime();
    glfwSetTime(0);

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
    if(_VDATA.window.fullscreen) {
        glfwSetWindowMonitor(_VDATA.window.window, NULL, _VDATA.window.position.x, _VDATA.window.position.y,
                             _VDATA.window.size.x, _VDATA.window.size.y, GLFW_DONT_CARE);
        _VDATA.window.fullscreen = false;
    } else {
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        glfwSetWindowMonitor(_VDATA.window.window, monitor, 0, 0, mode->width, mode->height, GLFW_DONT_CARE);
        _VDATA.window.fullscreen = true;
    }
}

void VFP(SetFullscreenKey)(VFP(KeyboardInput) key) {
    _VDATA.input.fullscreen_key = key;
}

void VFP(MaximizeWindow)() {
    glfwMaximizeWindow(_VDATA.window.window);
}

void VFP(MinimizeWindow)() {
    glfwIconifyWindow(_VDATA.window.window);
    PRINT("%d", _VDATA.window.flags & WINDOW_MINIMIZED);
}

void VFP(SetWindowFramerate)(int framerate) {
    if(framerate == 0)
        _VDATA.window.min_frame_time = 0;
    else
        _VDATA.window.min_frame_time = 1.f / framerate; /* Time in milliseconds */
}

double VFP(GetFramerate)() {
    return 1. / _VDATA.window.last_frame_time;
}

void VFP(ToggleWindowFlags)(int flags) {
    _VDATA.window.flags ^= flags;
}

size_t VFP(GetWindowFlags)() {
    return _VDATA.window.flags;
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

/*
*   Viewport functions
*/

static VFP(Viewport)* __get_viewport_pointer(VFP(ViewportID) id) {
    int lo = 0, hi = _VDATA.num_viewports - 1, mi = 0;
    while(lo <= hi){
        mi = lo + (hi - lo) / 2;
        if(_VDATA.viewports[mi]->id > id) {
            hi = mi - 1;
        } else if(_VDATA.viewports[mi]->id < id) {
            lo = mi + 1;
        } else {
            return _VDATA.viewports[mi];
        }
    }
    return 0;
}

static int __get_viewport_index(VFP(ViewportID) id) {
    int lo = 0, hi = _VDATA.num_viewports - 1, mi = 0;
    while(lo <= hi){
        mi = lo + (hi - lo) / 2;
        if(_VDATA.viewports[mi]->id > id) {
            hi = mi - 1;
        } else if(_VDATA.viewports[mi]->id < id) {
            lo = mi + 1;
        } else {
            return mi;
        }
    }
    return -1;
}

/* Debug print viewport arrays */
void __print_viewport_arr() {
    PRINT("[");
    for(int i = 0; i < MAX_VIEWPORTS; i++) {
        VFP(ViewportID) id = 0;
        id = _VDATA.viewports[i] ? _VDATA.viewports[i]->id : 0;
        PRINT("\t%p : %d", _VDATA.viewports[i], id);
    }
    PRINT("]");
}

/* Debug print viewport arrays */
void __print_children_arr(VFP(ViewportID) parent_id) {
    if(parent_id == -1) return;
    PRINT("Children of %d:\n[", parent_id);
    VFP(Viewport)* parent = __get_viewport_pointer(parent_id);
    for(int i = 0; i < MAX_CHILD_VIEWPORTS; i++) {
        PRINT("\t%d", parent->children[i]);
    }
    PRINT("]");
}

void _ExecuteDrawCommands(VFP(Viewport)* viewport) {
    //TODO: ^
}

VFP(ViewportID) VFP(RegisterViewport)(VFP(ViewportType) type, VFP(ViewportID) parent, VFP(Rectangle) rec) {
    /* Allocation and zero setting */
    if(_VDATA.num_viewports == MAX_VIEWPORTS) {
        __v_set_error_text("Failed to create viewport, reached max viewports", 49);
        return -1;
    }
    _VDATA.viewports[_VDATA.num_viewports] = malloc(sizeof(VFP(Viewport)));
    if(_VDATA.viewports[_VDATA.num_viewports] == 0) {
        __v_set_error_text("Failed to allocate memory", 26);
        return -1;
    }
    VFP(Viewport)* this = _VDATA.viewports[_VDATA.num_viewports];
    memset(this, 0, sizeof(VFP(Viewport)));

    /* Set the id number and update global state */
    if(_VDATA.num_viewports == 0) {
        this->id = 0;
    } else {
        this->id = _VDATA.viewports[_VDATA.num_viewports - 1]->id + 1;
    }
    _VDATA.num_viewports++;

    /* Set the viewport params */
    this->window.position.x = rec.x;
    this->window.position.y = rec.y;
    this->window.size.x = rec.width;
    this->window.size.y = rec.height;

    this->parent = parent;

    if(this->parent != -1) {
        VFP(Viewport)* p_parent = __get_viewport_pointer(parent);
        if(!p_parent) {
            __v_set_error_text("Parent viewport does not exist", 31);
            return -1;
        }
        p_parent->children[p_parent->num_children] = this->id;
        p_parent->num_children++;
    }

    this->type = type;

    this->window.background_color = (VFP(Color)){0, 0, 0, 0xFF};

    /* These are the default values (0) so they do not need to be explicitly set */
    //this->axis = VFP(VERTICAL_AXIS);
    //this->affinity = VFP(NO_AFFINITY);

    /* Diagnostics
    PRINT();
    PRINT("ID: %d", this->id);
    PRINT("Parent ID: %d", this->parent);
    PRINT("X: %d", this->window.position.x);
    PRINT("Y: %d", this->window.position.y);
    PRINT("Width: %d", this->window.size.x);
    PRINT("Height: %d", this->window.size.y);
    PRINT("Axis: %d", this->axis);
    PRINT("Affinity: %d", this->affinity);
    */

    /* Debug Viewport Array
    __print_viewport_arr();
    __print_children_arr(parent);
    */
    return this->id;
}

/* Free the memory associated with a viewport and remove it from the global array of viewports */
void __destroy_viewports_recursive(VFP(ViewportID) id) {
    int this_idx = __get_viewport_index(id);
    VFP(Viewport)* this = _VDATA.viewports[this_idx];

    for(int i = 0; i < this->num_children; i++) {
        __destroy_viewports_recursive(this->children[i]);
    }

    _VDATA.num_viewports--;
    free(this);
    _VDATA.viewports[this_idx] = 0;
}

/* The next two functions ensure that the viewport references are contiguously stored in their respective arrays */
/* This removes the framgentation of the Viewport pointers in the global viewport array */
void __defragment_viewport_array(VFP(Viewport)** array) {
    int move_back = 0;
    for(int i = 0; i < MAX_VIEWPORTS; i++) {
        if(move_back && array[i]) {
            array[i - move_back] = array[i];
            array[i] = 0;
        } else if(!array[i]) {
            move_back++;
        }
    }
}

/* This removes fragmentation of the child IDs array in a viewport */
void __defragment_child_viewport_array(VFP(Viewport)* parent) {
    int move_back = 0;
    for(int i = 0; i < MAX_CHILD_VIEWPORTS; i++) {
        if(move_back && parent->children[i]) {
            parent->children[i - move_back] = parent->children[i];
            parent->children[i] = 0;
        } else if(!parent->children[i]) {
            move_back++;
        }
    }
}

void VFP(UnregisterViewport)(VFP(ViewportID) id) {
    if(id < 0) {
        __v_set_error_text("Invalid viewport id sent to UnregisterViewport()", 49);
        return;
    }
    VFP(ViewportID) parent_id;
    VFP(Viewport)* parent;
    if(id != 0) {
        parent_id = __get_viewport_pointer(id)->parent;
        parent = __get_viewport_pointer(parent_id);
    } else {
        parent_id = -1;
        parent = 0;
    }

    if(parent) {
        for(int i = 0; i < MAX_CHILD_VIEWPORTS; i++) {
            if(parent->children[i] == id)
                parent->children[i] = 0;
        }
    }
    __destroy_viewports_recursive(id);

    /* Viewport arrays are guaranteed to be ordered low to high but not for child viewports to be contiguous */
    /* When the arrays are cleared the data must be restored to a contiguous series, hence defragmented */
    __defragment_viewport_array(_VDATA.viewports);
    if(parent)
        __defragment_child_viewport_array(parent);

    /* Debug Viewport Array
    __print_viewport_arr();
    __print_children_arr(parent_id);
    */
}
