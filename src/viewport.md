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

### Drawing Viewports

```txt
Viewport 0
{
    Viewport 1
    {
        Viewport 4
        Viewport 5
    }
    Viewport 2
    Viewport 3
}

Viewport 0 (Main Viewport)
{
    Horizontal Axis
    No Affinity (Forced)
    Static Type (Forced)
    No Min / Max Size (Forced)
    Children: 1, 2, 3
}

Viewport 1
{
    Vertical Axis
    Left Affinity
    Static Type
    No Min / Max Size
    Children: 4, 5
}

Viewport 2
{
    Vertical Axis
    Right Affinity
    Static Type
    No Min / Max Size
    Children: None
}

Viewport 3
{
    Vertical Axis
    Left Affinity
    Static Type
    No Min / Max Size
    Children: None
}

Resulting Window Should Look Like:
+---------------------------------------------+
| Icon               Title             - [] X |
+---------------------------------------------+
|               |              |              |
|  Viewport 1   | Viewport 3   | Viewport 2   |
|  Viewport 4   |              |              |
|               |              |              |
+---------------+              |              |
|               |              |              |
| Viewport 5    |              |              |
|               |              |              |
|               |              |              |
+---------------------------------------------+

If we added max values as such

Viewport 1
{
    Max Size: .25 width
}

Viewport 2
{
    Max Size: .25 width
}

Resulting Window Should Look Like:
+--------------------------------------------+
| Icon              Title             - [] X |
+--------------------------------------------+
|           |                    |           |
| Viewport 1|      Viewport 3    | Viewport 2|
| Viewport 4|                    |           |
|           |                    |           |
+-----------+                    |           |
|           |                    |           |
| Viewport 1|                    |           |
| Viewport 5|                    |           |
|           |                    |           |
+--------------------------------------------+

Order Of Operations for Viewport Drawing

Viewport Draw Direction
Default is left to right (Horizontal)

Order the child viewports
Create a list of the viewports and adjust the order

Find the actual size of each viewport
If size is specified then we subtract that amount of space from the available space
We then divide the remaining amount of space by the number of viewports left to get the size of each viewport

This is then repeated for each of the child viewports

WHEN TO ISSUE RECALCULATE SIZE COMMANDS
- When the window is resized the main viewport should be recalculated
    - This inlcudes fullscreen toggle, maximization, and restoration
    - Notably NOT including minimization
- When a new viewport is registered, its parent should be recalculated
- When a viewport is unregistered, its parent should be recalculated
- NOT When a viewport's type changes
- When a viewport is resized on its parent's cross axis, the first ancestor with a differing axis should be recalculated
    - i.e. when Viewport 5 is resized on its horizontal axis, then viewport 0 should be recalculated
- When a viewport is resized on its parent's main axis, its parent should be recalculated
    - i.e. when viewport 5 is resized on its vertical axis, then viewport 1 should be recalculated
- When a viewport's axis is changed, that viewport should be recalculated
    - i.e. when viewport 1 is changed to a horizontal axis, then viewport 1 should be recalculated
- When a docked viewport becomes hidden, its parent should be recalculated
- NOT When an undocked viewport is closed (becomes hidden)

WHEN TO RECALCULATE SIZE COMMANDS (In terms of function names)
- RegisterViewport()    ->  parent viewport
- UnregisterViewport()  ->  parent viewport
- ResizeViewport() on parent's main axis    ->  parent viewport
- ResizeViewport() on parent's cross axis   ->  first ancestor with axis differing parent's axis (or just the main axis)
- SetViewportAxis()     ->  this viewport
- SetViewportVisibility ->  parent viewport
- ToggleFullscreen()    ->  main viewport
- MaximizeWindow()      ->  main viewport
    - This will actually be triggered by the maximize callback
- SetWindowSize()       ->  main viewport
    - This will actually be triggered by the resize callback
- If SetViewportMaxSize() is less than the viewports draw size      ->  parent viewport
- If SetViewportMinSize() is greater than the viewports draw size   ->  parent viewport

```

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
