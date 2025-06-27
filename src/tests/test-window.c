#include <vuili.h>
#include <log.h>
#include <windows.h>

int main() {
    int flags = 0;
    int framerate = 60;
    V_ToggleWindowFlags(flags);
    V_SetWindowFramerate(framerate);
    V_InitWindow("Test Window", 500, 500, 1200, 800);

    while(!V_WindowShouldClose()) {
        //Main window rendering loop
        V_BeginDrawing();
        V_EndDrawing();
        V_SwapBuffers();
        Sleep(16);
    }

    V_CloseWindow();
}
