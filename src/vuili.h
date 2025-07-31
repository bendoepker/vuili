#ifndef _VUILI_H
#define _VUILI_H

/* For bool */
#include <stdbool.h>
#include <vuili-types.h>

void VFP(SleepX)(int milli);

/* Initialize the window context and create the window */
void VFP(InitWindow)(const char* title, int pos_x, int pos_y, int width, int height);

/* Close the window and uninitialize the context */
void VFP(CloseWindow)();

/* Clears the drawing of the previous frame */
void VFP(ClearFrame)();

/* Set the background color */
void VFP(SetBackgroundColor)(VFP(Color) color);

/* Begin Drawing for the current frame */
void VFP(BeginDrawing)();

/* End Drawing for the current frame, swap buffers and sleep for designated time */
void VFP(EndDrawing)();

/* Swap Frame Buffers (must not be currently drawing to the frame)*/
void VFP(SwapFrameBuffers)();

/* Poll the OS for any keyboard / mouse events */
void VFP(PollEvents)();

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

/* Set the key that will toggle fullscreen mode */
void VFP(SetFullscreenKey)(VFP(KeyboardInput) key);

/* Maximize the window */
void VFP(MaximizeWindow)();

/* Minimize the window */
void VFP(MinimizeWindow)();

/* Restore the window */
void VFP(RestoreWindow)();

/* Toggles the window flags for window creation */
void VFP(ToggleWindowFlags)(int flags);

/* Get the window flags toggled for the window  */
size_t VFP(GetWindowFlags)();

/* Set the window title */
void VFP(SetWindowTitle)(const char* title);

/* Set the max framerate for the window */
void VFP(SetWindowFramerate)(int framerate);

/* Get the framerate that the window is rendering at (In frames / second) */
double VFP(GetFramerate)();

/* Query to see if the window should close */
bool VFP(WindowShouldClose)();

/* Send a signal to close the window, sets the window should close flag */
void VFP(SetWindowShouldClose)();

/* Get the window position in screen space */
VFP(Vec2) VFP(GetWindowPos)();

/* Set the window position in screen space */
void VFP(SetWindowPosition)(int x, int y);

/* Get the window size */
VFP(Vec2) VFP(GetWindowSize)();

/* Set the window size */
void VFP(SetWindowSize)(int x, int y);

/* Get the position of the mouse in relation to the top left of the top left monitor */
VFP(Vec2) VFP(GetMousePositionAbsolute)();

/* Get the position of the mouse in relation to the top left of the window */
VFP(Vec2) VFP(GetMousePosition)();

/* Viewport functions */

/*
*/
VFP(Viewport)* VFP(RegisterViewport)(VFP(Viewport)* parent, int width, int height);

/* Deallocates viewport 'id' and all of its children and removes it from the global context */
void VFP(UnregisterViewport)(VFP(Viewport)* viewport);

/* Set the Viewport Type of 'id' */
void VFP(SetViewportType)(VFP(Viewport)* viewport, VFP(ViewportType) type);

/* Set the Viewport Axis of 'id' */
void VFP(SetViewportAxis)(VFP(Viewport)* viewport, VFP(ViewportAxis) axis);

/* Set the Size fo the Viewport 'id' */
void VFP(SetViewportSize)(VFP(Viewport)* viewport, unsigned int width, unsigned int height);

/* Set the Minimum Size of 'id' */
void VFP(SetViewportMinSize)(VFP(Viewport)* viewport, unsigned int width, unsigned int height);

/* Set the Maximum Size of 'id' */
void VFP(SetViewportMaxSize)(VFP(Viewport)* viewport, unsigned int width, unsigned int height);

/* Undock 'id' from its parent viewport */
void VFP(UndockViewport)(VFP(Viewport)* viewport);

/* Dock 'id' to its parent viewport */
void VFP(DockViewport)(VFP(Viewport)* viewport);

/* Set the background color of 'id' */
void VFP(SetViewportBackgroundColor)(VFP(Viewport)* viewport, VFP(Color) color);

/* Set the visibility of a viewport */
void VFP(SetViewportVisibility)(VFP(Viewport)* viewport, bool hidden);

#endif //_VUILI_H
