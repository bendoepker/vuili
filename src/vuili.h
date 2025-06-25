#ifndef _VUILI_H
#define _VUILI_H

/* For bool */
#include <stdbool.h>

/* Initialize the window context and create the window */
void V_InitWindow(const char* title, int pos_x, int pos_y, int width, int height);

/* Close the window and uninitialize the context */
void V_CloseWindow();

/* Toggle flags for the window without applying them (Useful before initializing the window) */
void V_ToggleWindowFlags(int flags);

/* Set the max framerate for the window */
void V_SetWindowFramerate(int framerate);

/* Toggle and apply the flags tot he window */
void V_ChangeWindowFlags(int flags);

/* Query to see if the window should close */
bool V_WindowShouldClose();

#endif //_VUILI_H
