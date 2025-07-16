#include <vuili.h>
#include <glad/gl.h>
#include <log.h>

int main() {

    // Window Setup
    //SleepX(5000);
    ToggleWindowFlags(TRANSPARENT_CLIENT | WINDOW_RESIZABLE | WINDOW_FULLSCREEN);
    InitWindow("Test Window", 500, 500, 1200, 800);
    PRINT("InitWindow Error (None if blank): %s", GetLastErrorText());
    SetWindowFramerate(60);
    ViewportID id1 = RegisterViewport(STATIC_VIEWPORT, 0, (Rectangle) { .x = 0, .y = 0, .width = 1200, .height = 800 });
    ViewportID id2 = RegisterViewport(STATIC_VIEWPORT, id1, (Rectangle) {0, 0, 1, 1});
    ViewportID id3 = RegisterViewport(STATIC_VIEWPORT, 0, (Rectangle) {0, 0, 1, 1});
    ViewportID id4 = RegisterViewport(STATIC_VIEWPORT, 0, (Rectangle) {0, 0, 1, 1});
    UnregisterViewport(id1);
    UnregisterViewport(id3);

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
    unsigned char x = 0;
    ToggleFullscreen();
    while(!WindowShouldClose()) {
        // Main Window Rendering Loop

        //SetBackgroundColor((Color) { .r = ++x, .g = x, .b = x, .a = 0xFF });

        // Input Handling...

        DrawFrame();
    }
#endif

    CloseWindow();
}
