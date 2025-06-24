#ifndef R_VIEWPORT_H
#define R_VIEWPORT_H

#include "raylib.h"
#include "config.h"

/*
*   unique ID number representing a viewport
*   -1 refers to a NULL ID (such as the parent ID of the main viewport)
*   0 refers to the main viewport
*   1 <-> MAX_VIEWPORTS are children of the main viewport or recursively children of those viewports
*/
typedef int ViewportID;

typedef struct { int x; int y; } Size;

typedef enum {
    STATIC_VIEWPORT = 0,        //Cannot be undocked from its parent viewport
    DYNAMIC_VIEWPORT = 1,       //Can be undocked from its parent viewport
    DOCKABLE_VIEWPORT = 1,      //Same as the dynamic viewport
} ViewportType;

typedef enum {
    VERTICAL_AXIS,              //Child viewports are aligned from top to bottom
    HORIZONTAL_AXIS,            //Child viewports are aligned from left to right
    REVERSE_VERTICAL_AXIS,      //Child viewports are aligned from bottom to top
    REVERSE_HORIZONTAL_AXIS,    //Child viewports are aligned from right to left
} ViewportAxis;

// ViewportAffinity == The side of the parent viewport that the viewport will align to
typedef enum {
    TOP_AFFINITY,               //Viewport will try to align to the top of its parent
    RIGHT_AFFINITY,               //Viewport will try to align to the right of its parent
    LEFT_AFFINITY,               //Viewport will try to align to the left of its parent
    BOTTOM_AFFINITY               //Viewport will try to align to the bottom of its parent,
} ViewportAffinity;

typedef struct {
    ViewportID parent;                          //Parent ID of the viewport
    unsigned int num_children;                  //Number of child viewports
    ViewportID children[MAX_CHILD_VIEWPORTS];   //Child viewport ID numbers
    ViewportType type;                          //Viewport type (docking / static)
    ViewportAxis axis;                          //Render flow of the viewport
    Rectangle drawable_area;

    //HACK: This model may not be great
    void (*DrawViewport)(void* params);         //Callback that will be called by DrawViewports()
    void* draw_params;                          //Parameters passed to DrawViewport(void* params)

    bool hidden;                                //Is the window shown in its parent's viewport? Ignored if undocked
    bool docked;                                //Is the window docked to its parent window

    //NOTE: When docked this should affect the parent's minimum size
    //      If either of these structs' fields are 0 then it should have no effect on its parent viewport
    Size minimum_size;                          //Minimum size of the viewport
    Size maximum_size;                          //Maximum size of the viewport

    //TODO: Insert fields for its own window if undocked

} Viewport;

/*
* Creates a viewport as a child of v_parent
*   return: Returns the ID of the new viewport if successfully created, otherwise returns -1
*
*   v_type: Type of viewport (dockable or not), also describes if the viewport will include
*           a menu bar at the top (minimize, maximize, close, and title)
*
*   v_parent: The parent viewport to the viewport being created, if this parameter is 0
*           then it will default to the main window's viewport
*
*/
ViewportID RegisterViewport(ViewportType v_type, ViewportID v_parent,
                            Rectangle v_rec, int x_min, int y_min, void (*DrawViewport)(void* params));

/*
* Sets the viewport axis of a viewport
*
*   v_id: ID of the viewport to set the axis of
*
*   v_axis: New axis to set it to
*/
void SetViewportAxis(ViewportID v_id, ViewportAxis v_axis);

/*
* Returns the viewport axis of a given viewport
*
*   return: The viewport axis of v_id, on error returns -1
*
*   v_id: ID of the viewport to get the axis of
*/
ViewportAxis GetViewportAxis(ViewportID v_id);

/*
* Renders all of the viewports from botton to top of the viewport tree,
* excludes hidden viewports and their children
*/
void DrawViewports();

/*
* Undocks a viewport from its parent if it is currently docked
*
*   v_id: ID of the viewport to undock
*/
void UndockViewport(ViewportID v_id);

/*
* Docks a viewport to its parent viewport if it is currently undocked
*
*   v_id: ID of the viewport to dock
*/
void DockViewport(ViewportID v_id);

/*
* Set the affinity of a viewport to its parent viewport
*
*   v_id: the ID of the viewport to set the affinity of
*
*   v_affinity: the affinity value to set (must be TOP_AFFINITY or BOTTOM_AFFINITY for ViewportAxis = vertical
*               and likewise respectively for ViewportAxis = horizontal)
*/
void SetViewportAffinity(ViewportID v_id, ViewportAffinity v_affinity);

/*
* Get the affinity set for a viewport
*
*   return: the ViewportAffinity of v_id
*
*   v_id: the ID of the viewport to get the affinity of
*/
ViewportAffinity GetViewportAffinity(ViewportID v_id);

#endif //R_VIEWPORT_H
