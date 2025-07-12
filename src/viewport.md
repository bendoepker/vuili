Viewports:
--------------

High level view:
    A window should be split into 'viewports' each viewport will either be static or dockable
(mutually exclusive states). Viewports will also grow in a tree, see depiction below.

```txt
            Main Window
           /     |     \
          /      |      \
  Viewport   Viewport    Viewport
             /      \
         Viewport Viewport

(note that 'Main Window' represents a viewport, but is always the root of the tree)
```

If any of these viewports get undocked from its parent viewport then all of its child viewports
will come with it, if a viewport is static then it cannot be undocked itself, but if its parent
becomes undocked then it will follow its parent

<br/>

Main window:
 - Minimum Screen size should be computed by the layout of the comprising viewports' minimum sizes
 - Parent of all other viewports, if it is closed then all subsequent viewports are closed

Static viewport:
 - Not dockable / undockable (Cannot create its own window)
 - The exception is that it follows its parent viewport's window (The parent viewport can still be undocked)

Dockable Viewport (Dynamic Viewport)
 - Variably docked / undocked from the main window
 - Will be closeable (when closed as an undocked window it will become 'hidden' and 'docked')

Viewport Object
- Window*: Pointer to the window that contains it, if null then it is in its parent's window
- Size (Vec2)
- Minimum Size  (Vec2)
- Maximum Size  (Vec2)
- Position      (Vec2)
- Input
    - Keyboard
    - Mouse

<br/>

### Main loop ex:

```c
//WindowShouldClose() refers to the state of the main window, not undocked dockable viewports
int main() {
    //If the parent viewport is 0 then the parent will be the main window
    int viewport_id = RegisterViewPort(DOCKABLE_VIEWPORT, parent_viewport)

    while(!WindowShouldClose()) {
        //Goes through each viewport and draws them whether they are docked or not
        DrawFrame();
    }

    void DrawFrame() {
        /* Poll Input events from the OS */
        PollEvents();

        /* Pass off events to the correct viewport */
        HandleEvents();

        /* Update state within the current viewport */
        /* This could mean changing internal values, render params, etc */
        UpdateState();

    }
}
```
