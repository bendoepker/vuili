#include <vuili.h>
#include <log.h>
#include <windows.h>

int main() {
    int flags = 0;
    int framerate = 60;
    V_ToggleWindowFlags(flags);
    V_SetWindowFramerate(framerate);
    V_InitWindow("Test Window", 500, 500, 1200, 800);
    V_SetMinWindowSize(100, 100);
    V_SetMaxWindowSize(1400, 1000);

    while(!V_WindowShouldClose()) {
        //Main window rendering loop
        Sleep(16);
    }

    V_CloseWindow();
}
