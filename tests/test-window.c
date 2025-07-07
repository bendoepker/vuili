#include <vuili.h>
#include <glad/gl.h>
#include <log.h>

int main() {

    // Window Setup
    //SleepX(5000);
    ToggleWindowFlags(TRANSPARENT_CLIENT | WINDOW_RESIZABLE);
    InitWindow("Test Window", 500, 500, 1200, 800);
    PRINT("InitWindow Error (None if blank): %s", GetLastErrorText());
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
    SetBackgroundColor((Color) { .r = 0x77, .g = 0x77, .b = 0x77, .a = 0x55 });
    while(!WindowShouldClose()) {
        // Main Window Rendering Loop

        // Input Handling...

        DrawFrame();
    }
#endif

    CloseWindow();
}
