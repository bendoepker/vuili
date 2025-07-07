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
    struct {
        Size mouse_pos;                                 //Mouse position in relation to main window
        Size mouse_pos_abs;                             //Mouse position in relation to desktop
        InputState mouse_state;                         //Mouse state

        //TODO: Keyboard input handling
    } input;
} VuiliData;

#endif
