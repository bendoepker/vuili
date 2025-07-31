#include <vuili.h>
#include <glad/gl.h>
#include <log.h>

int main() {

    Viewport* v1 = RegisterViewport(MAIN_VIEWPORT, 0, 0);
    Viewport* v2 = RegisterViewport(MAIN_VIEWPORT, 0, 0);
    // Window Setup
    ToggleWindowFlags(TRANSPARENT_CLIENT | WINDOW_RESIZABLE | WINDOW_FULLSCREEN);
    InitWindow("Test Window", 500, 500, 1200, 800);
    PRINT("InitWindow Error (None if blank): %s", GetLastErrorText());
    SetWindowFramerate(60);

    SetBackgroundColor((Color) { .r = 0x77, .g = 0x77, .b = 0x77, .a = 0x55 });
    unsigned char x = 0;
    ToggleFullscreen();
    while(!WindowShouldClose()) {
        // Main Window Rendering Loop

        // SetBackgroundColor((Color) { .r = ++x, .g = x, .b = x, .a = 0xFF });

        // Input Handling...

        DrawFrame();
    }

    // Cleanup
    CloseWindow();
}
