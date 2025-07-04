#include <vuili.h>
#include <log.h>

int main() {

    // Window Setup
    int flags = 0;
    int framerate = 60;
    ToggleWindowFlags(flags);
    SetWindowFramerate(framerate);
    InitWindow("Test Window", 500, 500, 1200, 800);
    SetWindowFramerate(60);

#if 0 // Immediate Mode Version
    while(!WindowShouldClose()) {
        // Main window rendering loop

        // Do any input handling here...

        BeginDrawing();

        // Do any drawing here...

        EndDrawing();
    }
#endif

#if 1 // Retained (ish?) Mode Version
    while(!WindowShouldClose()) {
        // Main Window Rendering Loop

        // Input Handling...
        if(GetMousePosition().x > 0) {
            ClearFrame();
        }

        DrawFrame();
    }
#endif

    CloseWindow();
}
