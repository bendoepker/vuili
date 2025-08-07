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
void _ExecuteDrawCommands(VFP(Viewport)* viewport);
void _ResizeViewport(VFP(Viewport)* viewport);
void _DrawViewportBackground(VFP(Viewport)* viewport);
GLuint _CreateShader(const char* vert_shader_path, const char* frag_shader_path);
void __print_viewport_sizes();

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
    _VDATA.viewport.draw_directions.size.x = x;
    _VDATA.viewport.draw_directions.size.y = y;
    _VDATA.viewport.draw_directions.resize = true;
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
    _VDATA.viewport.draw_directions.resize = true;
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
    if(key == KEY_G) {
        //WARN: TESTING ONLY
        __print_viewport_sizes();
    }
}

static void __mouse_callback(GLFWwindow* window, int button, int action, int mods) {
    (void)window;
}

GLuint _CreateShader(const char* vert_shader_path, const char* frag_shader_path) {
    /* Get the vertex shader as a string */
    FILE* vert_shader = fopen(vert_shader_path, "r");
    if(!vert_shader) {
        __v_set_error_text("Could not load the vertex shader", 33);
        return 0;
    }
    fseek(vert_shader, 0, SEEK_END);
    long vert_length = ftell(vert_shader);
    rewind(vert_shader);
    char* vert_src = malloc(vert_length + 1);
    memset(vert_src, 0, vert_length + 1);
    fread(vert_src, 1, vert_length, vert_shader);
    vert_src[vert_length] = '\0';
    fclose(vert_shader);

    /* Get the fragment shader as a string */
    FILE* frag_shader = fopen(frag_shader_path, "r");
    if(!frag_shader) {
        free(vert_src);
        __v_set_error_text("Could not load the fragment shader", 35);
        return 0;
    }
    fseek(frag_shader, 0, SEEK_END);
    long frag_length = ftell(frag_shader);
    rewind(frag_shader);
    char* frag_src = malloc(frag_length + 1);
    memset(frag_src, 0, frag_length + 1);
    fread(frag_src, 1, frag_length, frag_shader);
    frag_src[frag_length] = '\0';
    fclose(frag_shader);

    GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, (const char* const*)&vert_src, NULL);
    glCompileShader(vertex);
    free(vert_src);

    int success;
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if(!success) {
        char log[128];
        glGetShaderInfoLog(vertex, 128, NULL, log);
        log[127] = '\0';
        __v_set_error_text(log, 128);
        free(frag_src);
        return 0;
    }

    GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, (const char* const*)&frag_src, NULL);
    glCompileShader(fragment);
    free(frag_src);

    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if(!success) {
        char log[128];
        glGetShaderInfoLog(fragment, 128, NULL, log);
        log[127] = '\0';
        __v_set_error_text(log, 128);
        return 0;
    }

    GLuint program = glCreateProgram();
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);
    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if(!success) {
        char log[128];
        glGetProgramInfoLog(program, 128, NULL, log);
        log[127] = '\0';
        __v_set_error_text(log, 128);
        return 0;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return program;
}

void __viewport_init_opengl(VFP(Viewport)* viewport) {
    glGenBuffers(1, &viewport->draw_directions.vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, viewport->draw_directions.vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), viewport->draw_directions.vertices, GL_DYNAMIC_DRAW);
    for(int i = 0; i < viewport->num_children; i++) {
        __viewport_init_opengl(viewport->children[i]);
    }
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
    _VDATA.viewport.draw_directions.resize = true;
    _VDATA.viewport.draw_directions.vertices[0] = -1.0f;
    _VDATA.viewport.draw_directions.vertices[1] = 1.0f;
    _VDATA.viewport.draw_directions.vertices[3] = 1.0f;
    _VDATA.viewport.draw_directions.vertices[4] = 1.0f;
    _VDATA.viewport.draw_directions.vertices[6] = -1.0f;
    _VDATA.viewport.draw_directions.vertices[7] = -1.0f;
    _VDATA.viewport.draw_directions.vertices[9] = 1.0f;
    _VDATA.viewport.draw_directions.vertices[10] = -1.0f;
    glGenBuffers(1, &_VDATA.viewport.draw_directions.vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, _VDATA.viewport.draw_directions.vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), _VDATA.viewport.draw_directions.vertices, GL_STATIC_DRAW);

    _VDATA.background_shader = _CreateShader("../src/shaders/vertex.glsl", "../src/shaders/fragment.glsl");
    if(!_VDATA.background_shader) {
        return;
    }

    unsigned char background_indices[6] = {
        0, 2, 1,
        2, 3, 1
    };

    glGenBuffers(1, &_VDATA.background_ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _VDATA.background_ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned char), background_indices, GL_STATIC_DRAW);

    for(int i = 0; i < _VDATA.viewport.num_children; i++) {
        __viewport_init_opengl(_VDATA.viewport.children[i]);
    }

    /* No error */
    __v_set_error_text("", 1);
}

void VFP(CloseWindow)() {
    if(_VDATA.window.window)
        glfwDestroyWindow(_VDATA.window.window);
    for(int i = 0; i < _VDATA.viewport.num_children; i++) {
        UnregisterViewport(_VDATA.viewport.children[i]);
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

void _DrawViewportBackground(VFP(Viewport)* viewport) {
    glBindBuffer(GL_ARRAY_BUFFER, viewport->draw_directions.vertex_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _VDATA.background_ibo);
    glUseProgram(_VDATA.background_shader);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, NULL);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VFP(DrawFrame)() {

    /* Frame Drawing */
    VFP(ClearFrame)();

    int cur_num = 1;
    int next_num;
    VFP(Viewport)* cur_arr[_VDATA.num_reg_viewports];
    VFP(Viewport)* next_arr[_VDATA.num_reg_viewports];
    memset(cur_arr, 0, sizeof(VFP(Viewport)*) * _VDATA.num_reg_viewports);
    cur_arr[0] = &_VDATA.viewport;
    for(;;) { /* Span the depth of the tree */
        next_num = 0;
        memset(next_arr, 0, sizeof(VFP(Viewport)*) * _VDATA.num_reg_viewports);
        for(int i = 0, k = 0; i < cur_num; i++) { /* Span the width of the tree */
            if(cur_arr[i]->draw_directions.resize)
                _ResizeViewport(cur_arr[i]);

            if(!cur_arr[i]->hidden) {
                /* If the viewport is unhidden we will draw it to the framebuffer and add its children to the next draw list */
                _ExecuteDrawCommands(cur_arr[i]);
                next_num += cur_arr[i]->num_children;
                for(int j = 0; j < cur_arr[i]->num_children; j++) {
                    next_arr[k] = cur_arr[i]->children[j];
                    k++;
                }
            }
        }
        if(next_num == 0)
            break;
        cur_num = next_num;
        memset(cur_arr, 0, sizeof(VFP(Viewport)*) * _VDATA.num_reg_viewports);
        for(int i = 0; i < cur_num; i++) {
            cur_arr[i] = next_arr[i];
        }
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
    assert(_VDATA.window.window != NULL);
    if(_VDATA.window.fullscreen) {
        glfwSetWindowMonitor(_VDATA.window.window, NULL, _VDATA.window.position.x, _VDATA.window.position.y,
                             _VDATA.window.size.x, _VDATA.window.size.y, GLFW_DONT_CARE);
        _VDATA.window.fullscreen = false;
        _VDATA.viewport.draw_directions.size.x = _VDATA.window.size.x;
        _VDATA.viewport.draw_directions.size.y = _VDATA.window.size.y;
    } else {
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        glfwSetWindowMonitor(_VDATA.window.window, monitor, 0, 0, mode->width, mode->height, GLFW_DONT_CARE);
        _VDATA.window.fullscreen = true;
        int x, y;
        glfwGetWindowSize(_VDATA.window.window, &x, &y);
        _VDATA.viewport.draw_directions.size.x = x;
        _VDATA.viewport.draw_directions.size.y = y;
    }

    _VDATA.viewport.draw_directions.resize = true;
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
void __print_viewport_sizes() {
    int cur_num = 1;
    int next_num;
    VFP(Viewport)* cur_arr[64] = {0};
    VFP(Viewport)* next_arr[64] = {0};
    cur_arr[0] = &_VDATA.viewport;
    for(int i = 0; i < _VDATA.viewport.num_children; i++) {
        next_arr[i] = _VDATA.viewport.children[i];
    }
    for(;;) {
        /* Span the depth of the tree */
        next_num = 0;
        memset(next_arr, 0, sizeof(VFP(Viewport)*) * 64);
        printf("[ ");
        for(int i = 0, k = 0; i < cur_num; i++) {
            /* Span the width of the tree */
            printf("(%p TL: %f %f, TR: %f %f, BL: %f %f, BR: %f %f) ", cur_arr[i],
                   cur_arr[i]->draw_directions.vertices[0], cur_arr[i]->draw_directions.vertices[1],
                   cur_arr[i]->draw_directions.vertices[3], cur_arr[i]->draw_directions.vertices[4],
                   cur_arr[i]->draw_directions.vertices[6], cur_arr[i]->draw_directions.vertices[7],
                   cur_arr[i]->draw_directions.vertices[9], cur_arr[i]->draw_directions.vertices[10]
                   );
            next_num += cur_arr[i]->num_children;
            for(int j = 0; j < cur_arr[i]->num_children; j++) {
                next_arr[k] = cur_arr[i]->children[j];
                k++;
            }
        }
        printf("]\n");
        if(next_num == 0)
            break;
        cur_num = next_num;
        memset(cur_arr, 0, sizeof(VFP(Viewport)*) * 64);
        for(int i = 0; i < cur_num; i++) {
            cur_arr[i] = next_arr[i];
        }
    }
    PRINT();
}

void _ExecuteDrawCommands(VFP(Viewport)* viewport) {
    _DrawViewportBackground(viewport);
}

void _ResizeViewport(VFP(Viewport)* viewport) {
    /* A guard in case a leaf viewport has its axis changed or something */
    if(!viewport->num_children) {
        viewport->draw_directions.resize = false;
        return;
    }
    int remaining;
    int offset;
    int flex;
    int uncounted = viewport->num_children;
    bool horizontal = false;
    bool reverse = false;
    if(viewport->axis == VERTICAL_AXIS || viewport->axis == REVERSE_VERTICAL_AXIS) {
        remaining = viewport->draw_directions.size.y;
        offset = viewport->draw_directions.position.y;
    } else {
        horizontal = true;
        remaining = viewport->draw_directions.size.x;
        offset = viewport->draw_directions.position.x;
    }

    if(viewport->axis == REVERSE_VERTICAL_AXIS || viewport->axis == REVERSE_HORIZONTAL_AXIS)
        reverse = true;

    /* Calculate the amount of space needed for the fixed spacing viewports */
    for(int i = 0; i < viewport->num_children; i++) {
        if(viewport->children[i]->hidden) {
            uncounted--;
            continue;
        }
        if(horizontal) {
            if(viewport->children[i]->window.size.x) {
                remaining -= viewport->children[i]->window.size.x;
                uncounted--;
            }
        } else {
            if(viewport->children[i]->window.size.y && !viewport->children[i]->hidden) {
                remaining -= viewport->children[i]->window.size.y;
                uncounted--;
            }
        }
    }
    if(uncounted) {
        flex = remaining / uncounted;
    }

    VFP(Viewport)* unhidden_viewports[viewport->num_children];
    int j = 0;
    for(int i = 0; i < viewport->num_children; i++) {
        if(!viewport->children[i]->hidden) {
            unhidden_viewports[j] = viewport->children[i];
            j++;
        }
    }

    /* Assign the rectangle to each of the viewports */
    for(int i = 0; i < j; i++) {
        VFP(Viewport)* cur_child;

        /* This is a little odd, but if it is a reverse axis then we will work backwards throught the viewports */
        /* rather than adjusting the algorithm for how we find each of the viewport's positions */
        if(reverse) {
            cur_child = unhidden_viewports[(j - 1) - i];
        } else  {
            cur_child = unhidden_viewports[i];
        }

        if(horizontal) {
            if(cur_child->window.size.x) {
                cur_child->draw_directions.size.x = cur_child->window.size.x;
            } else {
                cur_child->draw_directions.size.x = flex;
            }

            cur_child->draw_directions.size.y = viewport->draw_directions.size.y;
            cur_child->draw_directions.position.y = viewport->draw_directions.position.y;

            cur_child->draw_directions.position.x = offset;
            offset += cur_child->draw_directions.size.x;
        } else {
            if(cur_child->window.size.y) {
                cur_child->draw_directions.size.y = cur_child->window.size.y;
            } else {
                cur_child->draw_directions.size.y = flex;
            }

            cur_child->draw_directions.size.x = viewport->draw_directions.size.x;
            cur_child->draw_directions.position.x = viewport->draw_directions.position.x;

            cur_child->draw_directions.position.y = offset;
            offset += cur_child->draw_directions.size.y;
        }

        /* Top Left */
        cur_child->draw_directions.vertices[0] = ((2.0f * cur_child->draw_directions.position.x) / (float)_VDATA.window.size.x) - 1.0f;
        cur_child->draw_directions.vertices[1] = 1.0f - ((2.0f * cur_child->draw_directions.position.y) / (float)_VDATA.window.size.y);

        /* Top Right */
        cur_child->draw_directions.vertices[2] = ((2.0f * (cur_child->draw_directions.position.x + cur_child->draw_directions.size.x)) / (float)_VDATA.window.size.x) - 1.0f;
        cur_child->draw_directions.vertices[3] = cur_child->draw_directions.vertices[1];

        /* Bottom Left */
        cur_child->draw_directions.vertices[4] = cur_child->draw_directions.vertices[0];
        cur_child->draw_directions.vertices[5] = 1.0f - ((2.0f * (cur_child->draw_directions.position.y + cur_child->draw_directions.size.y)) / (float)_VDATA.window.size.y);

        /* Bottom Right */
        cur_child->draw_directions.vertices[6] = cur_child->draw_directions.vertices[3];
        cur_child->draw_directions.vertices[7] = cur_child->draw_directions.vertices[7];

        glBindBuffer(GL_ARRAY_BUFFER, cur_child->draw_directions.vertex_buffer);
        glBufferSubData(GL_ARRAY_BUFFER, 0, 8 * sizeof(float), cur_child->draw_directions.vertices);

        if(cur_child->num_children)
            _ResizeViewport(cur_child);
    }

    viewport->draw_directions.resize = false;
}

void print_viewports() {
    int cur_num = 1;
    int next_num;
    VFP(Viewport)* cur_arr[64] = {0};
    VFP(Viewport)* next_arr[64] = {0};
    cur_arr[0] = &_VDATA.viewport;
    for(int i = 0; i < _VDATA.viewport.num_children; i++) {
        next_arr[i] = _VDATA.viewport.children[i];
    }
    for(;;) {
        /* Span the depth of the tree */
        next_num = 0;
        memset(next_arr, 0, sizeof(VFP(Viewport)*) * 64);
        printf("[ ");
        for(int i = 0, k = 0; i < cur_num; i++) {
            /* Span the width of the tree */
            printf("%p ", cur_arr[i]);
            next_num += cur_arr[i]->num_children;
            for(int j = 0; j < cur_arr[i]->num_children; j++) {
                next_arr[k] = cur_arr[i]->children[j];
                k++;
            }
        }
        printf("]\n");
        if(next_num == 0)
            break;
        cur_num = next_num;
        memset(cur_arr, 0, sizeof(VFP(Viewport)*) * 64);
        for(int i = 0; i < cur_num; i++) {
            cur_arr[i] = next_arr[i];
        }
    }
    PRINT();
}

VFP(Viewport)* VFP(RegisterViewport)(VFP(Viewport)* parent, int width, int height) {
    VFP(Viewport)* out = malloc(sizeof(VFP(Viewport)));
    if(!out) {
        __v_set_error_text("Could not allocate space for a viewport", 40);
        return 0;
    }
    memset(out, 0, sizeof(VFP(Viewport)));

    if(!parent) {
        if(_VDATA.viewport.num_children == MAX_CHILD_VIEWPORTS) {
            __v_set_error_text("Maximum amount of children reached", 35);
            free(out);
            return 0;
        }
        _VDATA.viewport.children[_VDATA.viewport.num_children] = out;
        _VDATA.viewport.num_children++;
        _VDATA.viewport.draw_directions.resize = true;
    } else {
        if(parent->num_children == MAX_CHILD_VIEWPORTS) {
            __v_set_error_text("Maximum amount of children reached", 35);
            free(out);
            return 0;
        }
        parent->children[parent->num_children] = out;
        parent->num_children++;
        out->parent = parent;
        parent->draw_directions.resize = true;
    }

    out->window.size.x = width;
    out->window.size.y = height;

    //PRINT("Registered: %p", out);
    //print_viewports();
    _VDATA.num_reg_viewports++;

    if(_VDATA.window.window) {
        glGenBuffers(1, &out->draw_directions.vertex_buffer);
        glBindBuffer(GL_ARRAY_BUFFER, out->draw_directions.vertex_buffer);
        glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), out->draw_directions.vertices, GL_DYNAMIC_DRAW);
    }

    return out;
}

void __defragment_viewport(VFP(Viewport)* viewport) {
    for(register int i = 0, m = 0; i < MAX_CHILD_VIEWPORTS; i++) {
        if(m && viewport->children[i]) {
            viewport->children[i - m] = viewport->children[i];
            viewport->children[i] = 0;
        }
        if(!viewport->children[i])
            m++;
    }
}

void __unregister_recursive(VFP(Viewport)* viewport) {
    for(int i = 0; i < viewport->num_children; i++) {
        __unregister_recursive(viewport->children[i]);
    }
    //PRINT("Unregistered: %p", viewport);
    _VDATA.num_reg_viewports--;
    free(viewport);
}
void VFP(UnregisterViewport)(VFP(Viewport)* viewport) {
    VFP(Viewport)* parent;
    if(!viewport->parent)
        parent = &_VDATA.viewport;
    else
        parent = viewport->parent;
    __unregister_recursive(viewport);
    for(int i = 0; i < parent->num_children; i++) {
        if(parent->children[i] == viewport) {
            parent->children[i] = 0;
            parent->num_children--;
            break;
        }
    }
    parent->draw_directions.resize = true;
    __defragment_viewport(parent);
    //print_viewports();
}

void VFP(SetViewportType)(VFP(Viewport)* viewport, VFP(ViewportType) type) {
    assert(viewport != 0 && "The main viewport's type cannot be changed");
    viewport->type = type;
}

void VFP(SetViewportAxis)(VFP(Viewport)* viewport, VFP(ViewportAxis) axis) {
    if(!viewport) {
        _VDATA.viewport.axis = axis;
        _VDATA.viewport.draw_directions.resize = true;
    }
    else {
        viewport->axis = axis;
        viewport->draw_directions.resize = true;
    }
}

void VFP(SetViewportSize)(VFP(Viewport)* viewport, unsigned int width, unsigned int height) {
    assert(viewport != 0 && "The main viewport's size cannot be changed independently of the window");
    viewport->window.size.x = width;
    viewport->window.size.y = height;
}

void VFP(SetViewportMinSize)(VFP(Viewport)* viewport, unsigned int width, unsigned int height) {
    assert(viewport != 0 && "The main viewport's minimum size cannot be changed independently of the window");
    viewport->window.min_size.x = width;
    viewport->window.min_size.y = height;
}

void VFP(SetViewportMaxSize)(VFP(Viewport)* viewport, unsigned int width, unsigned int height) {
    assert(viewport != 0 && "The main viewport's minimum size cannot be changed independently of the window");
    viewport->window.max_size.x = width;
    viewport->window.max_size.y = height;
    if(viewport->draw_directions.size.x > width || viewport->draw_directions.size.y > height) {
        if(!viewport->parent)
            _VDATA.viewport.draw_directions.resize = true;
        else
            viewport->parent->draw_directions.resize = true;
    }
}

void VFP(UndockViewport)(VFP(Viewport)* viewport) {
    assert(viewport != 0 && "The main viewport cannot be undocked from its parent viewport, that doesn't make sense");
    //TODO:
}

void VFP(DockViewport)(VFP(Viewport)* viewport) {
    assert(viewport != 0 && "The main viewport cannot be docked to a window, that doesn't make sense");
    //TODO:
}

void VFP(SetViewportBackgroundColor)(VFP(Viewport)* viewport, VFP(Color) color) {
    if(!viewport)
        _VDATA.viewport.window.background_color = color;
    else
        viewport->window.background_color = color;
}

void VFP(SetViewportVisibility)(VFP(Viewport)* viewport, bool hidden) {
    assert(viewport != 0 && "The main viewport's visibility cannot be changed, use the window visibility functions instead");
    viewport->hidden = hidden;
    if(!viewport->parent)
        _VDATA.viewport.draw_directions.resize = true;
    else
        viewport->parent->draw_directions.resize = true;
}
