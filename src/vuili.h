#ifndef _VUILI_H
#define _VUILI_H

/* For bool */
#include <stdbool.h>

/* Vuili Vector Types */
typedef struct { float x, y; } V_Vec2;
typedef struct { float x, y, z; } V_Vec3;
typedef struct { float x, y, z, a; } V_Vec4;

/* Vuili Color Type and Constants */
typedef struct { unsigned char r, g, b, a; } V_Color;
#define BLACK (V_Color){ 0x00, 0x00, 0x00, 0x00 }
#define WHITE (V_Color){ 0xFF, 0xFF, 0xFF, 0xFF }

/* Vuili Shape Types */
typedef struct { float x, y, width, height; } V_Rect;
typedef struct { V_Vec2 v1, v2, v3; } V_Tri;
typedef struct { float x1, y1, x2, y2; } V_Line;

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
} V_WindowFlags;

/* Initialize the window context and create the window */
void V_InitWindow(const char* title, int pos_x, int pos_y, int width, int height);

/* Close the window and uninitialize the context */
void V_CloseWindow();

/* Begin Drawing for the current frame */
void V_BeginDrawing();

/* End Drawing for the current frame, swap buffers and sleep for designated time */
void V_EndDrawing();

/* Swap Frame Buffers (must not be currently drawing to the frame)*/
void V_SwapBuffers();

/* Set the minimum size of a window */
void V_SetMinWindowSize(int width, int height);

/* Set the maximum size of a window */
void V_SetMaxWindowSize(int width, int height);

/* Unset the window maximum size */
void V_UnsetMaxWindowSize();

/* Unset the window minimum size */
void V_UnsetMinWindowSize();

/* Get the a description of the last error */
const char* V_GetLastErrorText();

/* Toggle the main window to fullscreen */
void V_ToggleFullscreen();

/* Toggle flags for the window without applying them (Useful before initializing the window) */
void V_ToggleWindowFlags(int flags);

/* Toggle and apply the flags to the window */
void V_ChangeWindowFlags(int flags);

/* Set the window title */
void V_SetWindowTitle(const char* title);

/* Set the max framerate for the window */
void V_SetWindowFramerate(int framerate);

/* Query to see if the window should close */
bool V_WindowShouldClose();

/* Send a signal to close the window, sets the window should close flag */
void V_SetWindowShouldClose();

/* Get the window position in screen space */
V_Vec2 V_GetWindowPos();

/* Set the window position in screen space */
void V_SetWindowPos(int x, int y);

/* Get the window size */
V_Vec2 V_GetWindowSize();

/* Set the window size */
void V_SetWindowSize(int x, int y);

/* Get the position of the mouse in relation to the top left of the top left monitor */
V_Vec2 V_GetMousePositionAbsolute();

/* Get the position of the mouse in relation to the top left of the window */
V_Vec2 V_GetMousePosition();

/* Get the drawable rectangle of the main window */
V_Rect V_GetWindowRect();

#endif //_VUILI_H
