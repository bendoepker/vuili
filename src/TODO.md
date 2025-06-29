# TODO
<!-- ✓ in vim: Insert + <C-v> + u + 2713-->
<!-- ✗ in vim: Insert + <C-v> + u + 2717-->

<br/>

## Library Utilities

- Error Handling
    - GetLastErrorText() ✓
    - GetLastError() ✗
- Inner Utility
    - High Resolution Timer ✗

## Basic Window Utilities

- Window Context
    - GetWindowSize() ✓
    - SetWindowSize() ✓
    - InitWindow() ✓
    - CloseWindow() ✓
    - WindowShouldClose() ✓
    - SetWindowShouldClose() ✓
    - SwapBuffers() ✓
    - SetMinWindowSize() ✓
    - SetMaxWindowSize() ✓
    - UnsetMinWindowSize() ✓
    - UnsetMaxWindowSize() ✓
    - MaximizeWindow() ✗
    - MinimizeWindow() ✗
    - ToggleFullscreen() ✗
    - ToggleWindowFlags() ✓
    - ChangeWindowFlags() ✗
    - SetWindowTitle() ✓
    - GetWindowPos() ✓
    - SetWindowPos() ✓
    - BeginDrawing() ✗
    - EndDrawing() ✗
    - SetWindowFramerate() ✗
    - GetWindowRect ✓
- Input Handling ✗
    - GetMousePos() -> Vec2 ✓
    - GetMousePosAbs() -> Vec2 ✓
    - GetMouseButton\[Down/Up/Pressed/Released\](Button) -> bool ✗
    - GetKey\[Down/Up/Pressed/Released\](Key) -> bool ✗
- Viewports ✗
    - Drawing to viewports ✗
    - Viewport Structure integration ✗
    - Detatchable windows ✗
- Drawing
    - Fonts
    - Shapes
        - Vector transformations (Rotations, Scale, Translations)
        - Rectangle
        - Triangle
        - 
