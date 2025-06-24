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
 - Can be undocked from a grandparent's viewport if its parent is undocked from it

Dockable Viewport (Dynamic Viewport)
 - Variably docked / undocked from the main window
 - Will be closeable (when closed as an undocked window it will become 'hidden' and 'docked')

<br/>

### Main loop ex:

```c
//WindowShouldClose() refers to the state of the main window, not undocked dockable viewports
int main() {
    //If the parent viewport is 0 then the parent will be the main window
    int viewport_id = RegisterViewPort(DOCKABLE_VIEWPORT, parent_viewport)

    while(!WindowShouldClose()) {
        //Frame setup code...Parse Inputs? Automatic State Change?
        DoSomethingEveryFrameBeforeDrawing();

        //Beginning of the usual raylib api...
        BeginDrawing();

        //Main viewport drawing in here
        DrawRectangle(SomeStuff, MoreStuff, RED);

        //Goes through each viewport and draws them whether they are docked or not
        DrawViewports();

        //Swap buffers for each of the windows and poll events for each window
        //This will work slightly differently from the way raylib typically works
        //as it will encompass all of the undocked windows as well as the main window
        EndDrawing();
    }
}
```
