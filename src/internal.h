#ifndef _VUILI_INTERNAL_H
#define _VUILI_INTERNAL_H
#include <stdint.h>
#include <stdbool.h>

/* glad and glfw */
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

/* Custom typedefs */
#include <vuili-types.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef float f32;
typedef double f64;
//typedef long double f128;

typedef struct {
    i32 x;
    i32 y;
} Size;
typedef Size Position;

#if (PLATFORM == WINDOWS)
    __declspec(dllimport) void __stdcall Sleep(unsigned long milli);
    #if defined(USE_HIGH_RES_TIMER)
        __declspec(dllimport) unsigned int timeBeginPeriod(unsigned int uPeriod);
        __declspec(dllimport) unsigned int timeEndPeriod(unsigned int uPeriod);
        typedef struct timecaps_tag {
            unsigned int wPeriodMin;
            unsigned int wPeriodMax;
        } TIMECAPS, *PTIMECAPS, *NPTIMECAPS, *LPTIMECAPS;
        __declspec(dllimport) unsigned int timeGetDevCaps(LPTIMECAPS ptc, unsigned int cbtc);
    #endif
#elif defined(__linux__)
    //TODO: Sleep function for linux
    #error Sleep function undefined for linux (internal.h)
#elif defined(__APPLE__)
    //TODO: Sleep function for MacOS
    #error Sleep function undefined for MacOS (internal.h)
#endif

typedef struct {
    VFP(ViewportID) id;                             //ID of this viewport
    VFP(ViewportID) parent;                         //Viewport ID of the parent viewport
    VFP(unsigned int) num_children;                 //Number of direct children of this viewport
    VFP(ViewportID) children[MAX_CHILD_VIEWPORTS];  //Viewport IDs of the direct children of this viewport
    VFP(ViewportType) type;                         //Viewport Type
    VFP(ViewportAxis) axis;                         //Render flow of the viewport
    VFP(ViewportAffinity) affinity;                 //Affinity to the parent viewport

    struct {
        GLFWwindow* window;                         //Pointer to the window containing this viewport, null if not undocked
        Size min_size;
        Size max_size;
        Size size;
        Position position;
        VFP(Color) background_color;
    } window;

    struct {
        struct {
            Position mouse_pos;
            VFP(InputState) mouse_state;
        } mouse;
        struct {

        } keyboard;
    } input;
} VFP(Viewport);

/* Global Variable (hidden from library user) */
typedef struct VuiliData {
    struct {
        Size min_size;                                  //Minimum size the window can be
        Size max_size;                                  //Maximum size the window can be
        Size size;                                      //Current size of the window
        Position position;
        u64 flags;
        bool maximized, minimized, fullscreen;          //Window is maximized / minimized / fullscreen
        bool should_close;                              //Should the window close
        bool drawing;
        double timer_resolution;                        //The timer resolution of the system (Windows)
        double min_frame_time;                          //Minimum frame time that a frame can take to render
        double last_frame_time;                         //Time that the last frame took to render
        VFP(Color) background_color;                    //Color painted on the background by glClear
        GLFWwindow* window;                             //Pointer to the GLFW window
    } window;

    /* It must be assured that there are no holes in this array if any viewports are removed */
    int num_viewports;                                  //Number of viewports registered
    VFP(Viewport)* viewports[MAX_VIEWPORTS];            //Array of viewports

    struct {
        /* Mouse Input */
        Position mouse_pos;                             //Mouse position in relation to main window
        Position mouse_pos_abs;                         //Mouse position in relation to desktop
        VFP(KeyboardInput) fullscreen_key;              //Key that toggles fullscreen

        /* Keyboard Input */
        VFP(KeyboardInput) last_key;
        bool last_key_double_pressed;
        double last_key_time;
    } input;
} VuiliData;

#endif
