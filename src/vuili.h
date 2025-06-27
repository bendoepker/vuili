#ifndef _VUILI_H
#define _VUILI_H

/* For bool */
#include <stdbool.h>

/* Vuili Vector Types */
typedef struct { float x, y; } V_Vec2;
typedef struct { float x, y, z; } V_Vec3;
typedef struct { float x, y, z, a; } V_Vec4;

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

/* End Drawing for the current frame */
void V_EndDrawing();

/* Swap Frame Buffers (must not be currently drawing to the frame)*/
void V_SwapBuffers();

/* Set the minimum size of a window */
void V_SetMinWindowSize(int width, int height);

/* Set the maximum size of a window */
void V_SetMaxWindowSize(int width, int height);

/* Get the a description of the last error */
const char* V_GetLastErrorText();

/* Toggle the main window to fullscreen */
void V_ToggleFullscreen();

/* Toggle flags for the window without applying them (Useful before initializing the window) */
void V_ToggleWindowFlags(int flags);

/* Toggle and apply the flags to the window */
void V_ChangeWindowFlags(int flags);

/* Set the max framerate for the window */
void V_SetWindowFramerate(int framerate);

/* Query to see if the window should close */
bool V_WindowShouldClose();

/* Send a signal to close the window, sets the window should close flag */
void V_SetWindowShouldClose();

/* Get the position of the mouse in relation to the top left of the top left monitor */
V_Vec2 V_GetMousePositionAbsolute();

/* Get the position of the mouse in relation to the top left of the window */
V_Vec2 V_GetMousePosition();

#endif //_VUILI_H
