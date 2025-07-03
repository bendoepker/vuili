#ifndef _VUILI_H
#define _VUILI_H

/* For bool */
#include <stdbool.h>
#include <config.h>

/*
* #define VUILI_FUNCTION_PREFIX to enable function prefixes
*/
#ifdef VUILI_FUNCTION_PREFIX
    #define VFP(x) V_##x
#else
    #define VFP(x) x
#endif

/* Vuili Vector Types */
typedef struct { float x, y; } VFP(Vec2);
typedef struct { float x, y, z; } VFP(Vec3);
typedef struct { float x, y, z, a; } VFP(Vec4);

/* Vuili Color Type and Constants */
typedef struct { unsigned char r, g, b, a; } VFP(Color);
#define BLACK (VFP(Color)){ 0x00, 0x00, 0x00, 0x00 }
#define WHITE (VFP(Color)){ 0xFF, 0xFF, 0xFF, 0xFF }

/* Vuili Shape Types */
typedef struct { float x, y, width, height; } VFP(Rect);
typedef struct { VFP(Vec2) v1, v2, v3; } VFP(Tri);
typedef struct { float x1, y1, x2, y2; } VFP(Line);

typedef enum {
    //TODO:
    WINDOW_RESIZABLE    = 0x00000001ull,
    WINDOW_FULLSCREEN   = 0x00000002ull,
    FLAG_UNUSED00       = 0x00000004ull,
    FLAG_UNUSED01       = 0x00000008ull,
    FLAG_UNUSED02       = 0x00000010ull,
    FLAG_UNUSED03       = 0x00000020ull,
    FLAG_UNUSED04       = 0x00000040ull,
    FLAG_UNUSED05       = 0x00000080ull,
    FLAG_UNUSED06       = 0x00000100ull,
    FLAG_UNUSED07       = 0x00000200ull,
    FLAG_UNUSED08       = 0x00000400ull,
    FLAG_UNUSED09       = 0x00000800ull,
} VFP(WindowFlags);

/* Initialize the window context and create the window */
void VFP(InitWindow)(const char* title, int pos_x, int pos_y, int width, int height);

/* Close the window and uninitialize the context */
void VFP(CloseWindow)();

/* Clears the drawing of the previous frame */
void VFP(ClearFrame)(VFP(Color) color);

/* Begin Drawing for the current frame */
void VFP(BeginDrawing)();

/* End Drawing for the current frame, swap buffers and sleep for designated time */
void VFP(EndDrawing)();

/* Swap Frame Buffers (must not be currently drawing to the frame)*/
void VFP(SwapBuffers)();

/* Retained mode drawing */
void VFP(DrawFrame)();

/* Set the minimum size of a window */
void VFP(SetMinWindowSize)(int width, int height);

/* Set the maximum size of a window */
void VFP(SetMaxWindowSize)(int width, int height);

/* Unset the window maximum size */
void VFP(UnsetMaxWindowSize)();

/* Unset the window minimum size */
void VFP(UnsetMinWindowSize)();

/* Get the a description of the last error */
const char* VFP(GetLastErrorText)();

/* Toggle the main window to fullscreen */
void VFP(ToggleFullscreen)();

/* Toggle flags for the window without applying them (Useful before initializing the window) */
void VFP(ToggleWindowFlags)(int flags);

/* Toggle and apply the flags to the window */
void VFP(ChangeWindowFlags)(int flags);

/* Set the window title */
void VFP(SetWindowTitle)(const char* title);

/* Set the max framerate for the window */
void VFP(SetWindowFramerate)(int framerate);

/* Query to see if the window should close */
bool VFP(WindowShouldClose)();

/* Send a signal to close the window, sets the window should close flag */
void VFP(SetWindowShouldClose)();

/* Get the window position in screen space */
VFP(Vec2) VFP(GetWindowPos)();

/* Set the window position in screen space */
void VFP(SetWindowPos)(int x, int y);

/* Get the window size */
VFP(Vec2) VFP(GetWindowSize)();

/* Set the window size */
void VFP(SetWindowSize)(int x, int y);

/* Get the position of the mouse in relation to the top left of the top left monitor */
VFP(Vec2) VFP(GetMousePositionAbsolute)();

/* Get the position of the mouse in relation to the top left of the window */
VFP(Vec2) VFP(GetMousePosition)();

/* Get the drawable rectangle of the main window */
VFP(Rect) VFP(GetWindowRect)();

#endif //_VUILI_H
