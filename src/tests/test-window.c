#include <vuili.h>

int main() {
    int flags = 0;
    int framerate = 60;
    V_ToggleWindowFlags(flags);
    V_SetWindowFramerate(framerate);
    V_InitWindow("Test Window", 500, 500, 1200, 800);

    while(!V_WindowShouldClose()) {
    }

    V_CloseWindow();
}
