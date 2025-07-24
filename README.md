Vuili
=====

(V)iewport (UI) (Li)brary
-------------------------

<br/>

Current Feature Set
-------------------

<h3> Window </h3>

Creation and Destruction
- ToggleWindowFlags()
- GetWindowFlags()
- InitWindow() (Partial)
- CloseWindow()
- WindowShouldClose()
- SetWindowShouldClose()

Window Context
- GetWindowSize()
- SetWindowSize()
- SetMinWindowSize()
- SetMaxWindowSize()
- UnsetMinWindowSize()
- UnsetMaxWindowSize()
- SetWindowTitle()
- GetWindowPos()
- SetWindowPos()

Window Drawing
- SwapBuffers()
- SetWindowFramerate()
- GetFramerate()
- MaximizeWindow()
- MinimizeWindow()
- ToggleFullscreen()
- DrawFrame() (Partial)

<h3> Input Handling </h3>

Keyboard
- SetFullscreenKey()

Mouse
- GetMousePos()
- GetMousePosAbs()

Planned Feature Set (TODO's)
----------------------------

<h3> Window </h3>

Creation and Destruction
- InitWindow() (Custom Titlebar)
- Splash Screen

Viewports
- Individual Viewport Drawing
- Detatching Viewports (Relies on custom titlebars)
- Immediate Mode Functionality (Un-prioritized)

Drawing
- Predefined Color List
- Custom Shaders
- Fonts
- Shapes
- UI Elements
    - Buttons
    - Slider
    - Text Boxes
    - Scroll Bars

<h3> Input Handling </h3>

Keyboard
- GetKey\[Down | Up | Pressed | Released\](Key)

Mouse
- GetMouseButton\[Down | Up | Pressed | Released\](Button)

<h3> Other </h3>

Unprioritized Features
- Undo / Redo
- Config File
- Light / Dark Mode Recognition
