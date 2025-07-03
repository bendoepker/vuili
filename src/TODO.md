# TODO
<!-- ✓ in vim: Insert + <C-v> + u + 2713-->
<!-- ✗ in vim: Insert + <C-v> + u + 2717-->

<br/>

## Library Utilities

- Error Handling
    - GetLastErrorText() ✓
    - GetLastError() ✗
- Inner Utility
    - High Resolution Timer ✓

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
    - ToggleWindowFlags() ✓
    - SetWindowTitle() ✓
    - GetWindowPos() ✓
    - SetWindowPos() ✓
    - SetWindowFramerate() ✓
    - GetWindowRect ✓

    - ClearBackground() ✗
    - MaximizeWindow() ✗
    - MinimizeWindow() ✗
    - ToggleFullscreen() ✗
    - ChangeWindowFlags() ✗
    - BeginDrawing() ✗ (Partial)
    - EndDrawing() ✗ (Partial)
    - Viewports ✗
        - Retained Mode Drawing ✗
        - Framework
    - Custom Window Frame
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
    - Shader loader / management functions
    - Textures / texture manipulation
    - Fonts
    - Shapes
        - Vector transformations (Rotations, Scale, Translations)
        - Rectangle
        - Triangle
- UI Tools ✗
    - Buttons
    - Sliders
    - Text Box
    - Scroll Bars
- Unsorted Feature Set ✗
    - Undo / Redo
    - Config File Read / Write
    - Light / Dark mode recognization
