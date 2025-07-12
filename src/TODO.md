# TODO
<!-- ✓ in vim: Insert + <C-v> + u + 2713-->
<!-- ✗ in vim: Insert + <C-v> + u + 2717-->

<br/>

## BREAKING / ASAP

- 

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
    - CloseWindow() ✓
    - WindowShouldClose() ✓
    - SetWindowShouldClose() ✓
    - SwapBuffers() ✓
    - SetMinWindowSize() ✓
    - SetMaxWindowSize() ✓
    - UnsetMinWindowSize() ✓
    - UnsetMaxWindowSize() ✓
    - ToggleWindowFlags() ✓
    - ChangeWindowFlags() ✓ (Pending ApplyWindowFlags())
    - GetWindowFlags() ✓
    - SetWindowTitle() ✓
    - GetWindowPos() ✓
    - SetWindowPos() ✓
    - SetWindowFramerate() ✓
    - GetFramerate() ✓
    - MaximizeWindow() ✓
    - MinimizeWindow() ✓
    - ToggleFullscreen() ✓
    - DrawFrame() ✓ (Partial)
        - Timing functions improvement to get more accurate framerate (Not prioritized, its accurate enough)
        - Need to render all draw calls
    - InitWindow() ✓ (Partial)
        - Window Creation Flags
            - WINDOW_RESIZEABLE ✓
            - TRANSPARENT_CLIENT ✓
            - CUSTOM_TITLEBAR ✗
            - WINDOW_UNFOCUSED ✓
            - WINDOW_FULLSCREEN ✓
            - WINDOW_MAXIMIZED ✓
            - WINDOW_MINIMIZED ✓

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
