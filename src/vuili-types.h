#ifndef _V_TYPES_H
#define _V_TYPES_H

#include "config.h"
#include "stddef.h"

/* Vuili Vector Types */
typedef struct { float x, y; } VFP(Vec2);
typedef struct { float x, y, z; } VFP(Vec3);
typedef struct { float x, y, z, a; } VFP(Vec4);

/* Vuili Color Type and Constants */
typedef struct { unsigned char r, g, b, a; } VFP(Color);
#define BLACK (VFP(Color)){ 0x00, 0x00, 0x00, 0x00 }
#define WHITE (VFP(Color)){ 0xFF, 0xFF, 0xFF, 0xFF }

/* Vuili Shape Types */
typedef struct { float x, y, width, height; } VFP(Rectangle);
typedef struct { VFP(Vec2) v1, v2, v3; } VFP(Triangle);
typedef struct { float x1, y1, x2, y2; } VFP(Line);

typedef enum {
    /* NOTE: These must be set before window creation */
    WINDOW_RESIZABLE    = 0x00000001ull,    //Window will be resizeable in windowed mode
    WINDOW_UNFOCUSED    = 0x00000002ull,    //Window will be unfocused on opening
    TRANSPARENT_CLIENT  = 0x00000004ull,    //Client area will be transparent,
    CUSTOM_TITLEBAR     = 0x00000008ull,    //Window will have a customizable title bar     //TODO:
    WINDOW_FULLSCREEN   = 0x00000010ull,    //Window will be set to fullscreen              //TODO:
    WINDOW_MAXIMIZED    = 0x00000020ull,    //Window will be maximized on opening
    WINDOW_MINIMIZED    = 0x00000040ull,    //Window will be minimized on opening

    /* Reserved flags */
    FLAG_UNUSED05       = 0x00000080ull,
    FLAG_UNUSED06       = 0x00000100ull,
    FLAG_UNUSED07       = 0x00000200ull,
    FLAG_UNUSED08       = 0x00000400ull,
    FLAG_UNUSED09       = 0x00000800ull,
    FLAG_UNUSED10       = 0x00001000ull,
    FLAG_UNUSED11       = 0x00002000ull,
    FLAG_UNUSED12       = 0x00004000ull,
    FLAG_UNUSED13       = 0x00008000ull,
} VFP(WindowFlags);

//Key codes align with GLFW key codes
typedef enum {
    VFP(KEY_NONE)           = 0,
    VFP(KEY_SPACE)          = 32,
    VFP(KEY_APOSTROPHE)     = 39, /* ' */
    VFP(KEY_COMMA)          = 44, /* , */
    VFP(KEY_MINUS)          = 45, /* - */
    VFP(KEY_PERIOD)         = 46, /* . */
    VFP(KEY_SLASH)          = 47, /* / */
    VFP(KEY_0)              = 48,
    VFP(KEY_1)              = 49,
    VFP(KEY_2)              = 50,
    VFP(KEY_3)              = 51,
    VFP(KEY_4)              = 52,
    VFP(KEY_5)              = 53,
    VFP(KEY_6)              = 54,
    VFP(KEY_7)              = 55,
    VFP(KEY_8)              = 56,
    VFP(KEY_9)              = 57,
    VFP(KEY_SEMICOLON)      = 59, /* ; */
    VFP(KEY_EQUAL)          = 61, /* = */
    VFP(KEY_A)              = 65,
    VFP(KEY_B)              = 66,
    VFP(KEY_C)              = 67,
    VFP(KEY_D)              = 68,
    VFP(KEY_E)              = 69,
    VFP(KEY_F)              = 70,
    VFP(KEY_G)              = 71,
    VFP(KEY_H)              = 72,
    VFP(KEY_I)              = 73,
    VFP(KEY_J)              = 74,
    VFP(KEY_K)              = 75,
    VFP(KEY_L)              = 76,
    VFP(KEY_M)              = 77,
    VFP(KEY_N)              = 78,
    VFP(KEY_O)              = 79,
    VFP(KEY_P)              = 80,
    VFP(KEY_Q)              = 81,
    VFP(KEY_R)              = 82,
    VFP(KEY_S)              = 83,
    VFP(KEY_T)              = 84,
    VFP(KEY_U)              = 85,
    VFP(KEY_V)              = 86,
    VFP(KEY_W)              = 87,
    VFP(KEY_X)              = 88,
    VFP(KEY_Y)              = 89,
    VFP(KEY_Z)              = 90,
    VFP(KEY_LEFT_BRACKET)   = 91, /* [ */
    VFP(KEY_BACKSLASH)      = 92, /* \ */
    VFP(KEY_RIGHT_BRACKET)  = 93, /* ] */
    VFP(KEY_GRAVE_ACCENT)   = 96, /* ` */
    VFP(KEY_WORLD_1)        = 161, /* non-US #1 */
    VFP(KEY_WORLD_2)        = 162, /* non-US #2 */

    /* Function keys */
    VFP(KEY_ESCAPE)         = 256,
    VFP(KEY_ENTER)          = 257,
    VFP(KEY_TAB)            = 258,
    VFP(KEY_BACKSPACE)      = 259,
    VFP(KEY_INSERT)         = 260,
    VFP(KEY_DELETE)         = 261,
    VFP(KEY_RIGHT)          = 262,
    VFP(KEY_LEFT)           = 263,
    VFP(KEY_DOWN)           = 264,
    VFP(KEY_UP)             = 265,
    VFP(KEY_PAGE_UP)        = 266,
    VFP(KEY_PAGE_DOWN)      = 267,
    VFP(KEY_HOME)           = 268,
    VFP(KEY_END)            = 269,
    VFP(KEY_CAPS_LOCK)      = 280,
    VFP(KEY_SCROLL_LOCK)    = 281,
    VFP(KEY_NUM_LOCK)       = 282,
    VFP(KEY_PRINT_SCREEN)   = 283,
    VFP(KEY_PAUSE)          = 284,
    VFP(KEY_F1)             = 290,
    VFP(KEY_F2)             = 291,
    VFP(KEY_F3)             = 292,
    VFP(KEY_F4)             = 293,
    VFP(KEY_F5)             = 294,
    VFP(KEY_F6)             = 295,
    VFP(KEY_F7)             = 296,
    VFP(KEY_F8)             = 297,
    VFP(KEY_F9)             = 298,
    VFP(KEY_F10)            = 299,
    VFP(KEY_F11)            = 300,
    VFP(KEY_F12)            = 301,
    VFP(KEY_F13)            = 302,
    VFP(KEY_F14)            = 303,
    VFP(KEY_F15)            = 304,
    VFP(KEY_F16)            = 305,
    VFP(KEY_F17)            = 306,
    VFP(KEY_F18)            = 307,
    VFP(KEY_F19)            = 308,
    VFP(KEY_F20)            = 309,
    VFP(KEY_F21)            = 310,
    VFP(KEY_F22)            = 311,
    VFP(KEY_F23)            = 312,
    VFP(KEY_F24)            = 313,
    VFP(KEY_F25)            = 314,
    VFP(KEY_KP_0)           = 320,
    VFP(KEY_KP_1)           = 321,
    VFP(KEY_KP_2)           = 322,
    VFP(KEY_KP_3)           = 323,
    VFP(KEY_KP_4)           = 324,
    VFP(KEY_KP_5)           = 325,
    VFP(KEY_KP_6)           = 326,
    VFP(KEY_KP_7)           = 327,
    VFP(KEY_KP_8)           = 328,
    VFP(KEY_KP_9)           = 329,
    VFP(KEY_KP_DECIMAL)     = 330,
    VFP(KEY_KP_DIVIDE)      = 331,
    VFP(KEY_KP_MULTIPLY)    = 332,
    VFP(KEY_KP_SUBTRACT)    = 333,
    VFP(KEY_KP_ADD)         = 334,
    VFP(KEY_KP_ENTER)       = 335,
    VFP(KEY_KP_EQUAL)       = 336,
    VFP(KEY_LEFT_SHIFT)     = 340,
    VFP(KEY_LEFT_CONTROL)   = 341,
    VFP(KEY_LEFT_ALT)       = 342,
    VFP(KEY_LEFT_SUPER)     = 343,
    VFP(KEY_RIGHT_SHIFT)    = 344,
    VFP(KEY_RIGHT_CONTROL)  = 345,
    VFP(KEY_RIGHT_ALT)      = 346,
    VFP(KEY_RIGHT_SUPER)    = 347,
    VFP(KEY_MENU)           = 348,
} VFP(KeyboardInput);

typedef enum {
    VFP(MOUSE_LEFT)         = 0,
    VFP(MOUSE_RIGHT)        = 1,
    VFP(MOUSE_MIDDLE)       = 2,

    VFP(MOUSE_BUTTON_1)     = VFP(MOUSE_LEFT),
    VFP(MOUSE_BUTTON_2)     = VFP(MOUSE_RIGHT),
    VFP(MOUSE_BUTTON_3)     = VFP(MOUSE_MIDDLE),
    VFP(MOUSE_BUTTON_4)     = 3,
    VFP(MOUSE_BUTTON_5)     = 4,
    VFP(MOUSE_BUTTON_6)     = 5,
    VFP(MOUSE_BUTTON_7)     = 6,
    VFP(MOUSE_BUTTON_8)     = 7,
} VFP(MouseInput);

typedef enum {
    VFP(RELEASED)           = 0,
    VFP(PRESSED)            = 1,
    VFP(ALT_PRESSED)        = 2,
    VFP(CTRL_PRESSED)       = 3,
    VFP(SHIFT_PRESSED)      = 4,
} VFP(InputState);

/*
*   unique ID number representing a viewport
*   -1 refers to a NULL ID (such as the parent ID of the main viewport)
*   0 refers to the main viewport
*   1 <-> MAX_VIEWPORTS are children of the main viewport or recursively children of those viewports
*/
typedef int VFP(ViewportID);

typedef enum {
    VFP(STATIC_VIEWPORT) = 0,                   //Cannot be undocked from its parent viewport
    VFP(DYNAMIC_VIEWPORT) = 1,                  //Can be undocked from its parent viewport
    VFP(DOCKABLE_VIEWPORT) = 1,                 //Same as the dynamic viewport
    VFP(FLOATING_VIEWPORT) = 2,                 //Bound to its parent viewport's window but floating within it
} VFP(ViewportType);

typedef enum {
    VFP(HORIZONTAL_AXIS) = 0,                   //Child viewports are aligned from left to right
    VFP(VERTICAL_AXIS) = 1,                     //Child viewports are aligned from top to bottom
    VFP(REVERSE_HORIZONTAL_AXIS) = 2,           //Child viewports are aligned from right to left
    VFP(REVERSE_VERTICAL_AXIS) = 3,             //Child viewports are aligned from bottom to top
} VFP(ViewportAxis);

// ViewportAffinity == The side of the parent viewport that the viewport will align to
typedef enum {
    VFP(NO_AFFINITY) = 0,                       //Viewport will not make any specific allignment attempts
    VFP(FAR_AFFINITY) = 1,                      //Viewport will try to allign to the far side of the viewport's axis
    VFP(CLOSE_AFFINITY) = 2,                    //Viewport will try to allign to the close side of the viewport's axis
} VFP(ViewportAffinity);

#endif //_V_TYPES_H
