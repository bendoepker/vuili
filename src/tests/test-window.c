#include <vuili.h>
#include <log.h>
#include <windows.h>

int main() {

    // Window Setup
    int flags = 0;
    int framerate = 60;
    V_ToggleWindowFlags(flags);
    V_SetWindowFramerate(framerate);
    V_InitWindow("Test Window", 500, 500, 1200, 800);
    V_SetWindowFramerate(60);

#if 0 // Immediate Mode Version
    while(!V_WindowShouldClose()) {
        // Main window rendering loop

        // Do any input handling here...

        V_BeginDrawing();

        // Do any drawing here...

        V_EndDrawing();
    }
#endif

#if 1 // Retained (ish?) Mode Version
    while(!V_WindowShouldClose()) {
        // Main Window Rendering Loop

        // Input Handling...

        V_DrawFrame();
    }
#endif

    V_CloseWindow();
}
