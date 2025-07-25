# TODO
<!-- ✓ in vim: Insert + <C-v> + u + 2713-->
<!-- ✗ in vim: Insert + <C-v> + u + 2717-->

<br/>

## BREAKING / ASAP

- Per Viewport Draw Commands List and Execution
    - _ExecuteDrawCommands() ^
    - Recalculate Size Commands

## NON-BREAKING / NON-ASAP

- Define Viewports before window creation
- Change SetWindowFramerate() to SetFramerate()
- RestoreWindow()

<br/>

## Library Utilities

- Error Handling
    - GetLastErrorText() ✓
    - GetLastError() ✗
- Inner Utility
    - High Resolution Timer ✓

## Basic Window Utilities

- Window Context
    - ToggleWindowFlags() ✓
    - GetWindowFlags() ✓
    - InitWindow() ✓ (Partial)
        - Window Creation Flags
            - WINDOW_RESIZEABLE ✓
            - TRANSPARENT_CLIENT ✓
            - CUSTOM_TITLEBAR ✗
            - WINDOW_UNFOCUSED ✓
            - WINDOW_FULLSCREEN ✓
            - WINDOW_MAXIMIZED ✓
            - WINDOW_MINIMIZED ✓
    - SetWindowShouldClose() ✓
    - WindowShouldClose() ✓
    - CloseWindow() ✓
    - GetWindowSize() ✓
    - SetWindowSize() ✓
    - SetMinWindowSize() ✓
    - SetMaxWindowSize() ✓
    - UnsetMinWindowSize() ✓
    - UnsetMaxWindowSize() ✓
    - SetWindowTitle() ✓
    - GetWindowPos() ✓
    - SetWindowPos() ✓
    - SwapBuffers() ✓
    - SetWindowFramerate() ✓
    - GetFramerate() ✓
    - MaximizeWindow() ✓
    - MinimizeWindow() ✓
    - ToggleFullscreen() ✓
    - DrawFrame() ✓ (Partial)
        - Need to render all draw calls
    - Viewport Structure integration ✓

    - Immediate mode functions
        - I would like to stray away from an immediate mode GUI at the moment
        - ClearBackground() ✗
        - BeginDrawing() ✗ (Partial)
        - EndDrawing() ✗ (Partial)
    - Viewports ✗
        - Retained Mode Drawing ✗
        - Framework
    - Custom Window Frame
- Input Handling ✗
    - SetFullscreenKey() ✓
    - GetMousePos() -> Vec2 ✓
    - GetMousePosAbs() -> Vec2 ✓

    - GetMouseButton\[Down/Up/Pressed/Released\](Button) -> bool ✗
    - GetKey\[Down/Up/Pressed/Released\](Key) -> bool ✗
- Viewports ✗
    - Drawing to viewports ✗
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
