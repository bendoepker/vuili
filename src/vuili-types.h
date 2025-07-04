#ifndef _V_TYPES_H
#define _V_TYPES_H

#include "config.h"

/* Vuili Vector Types */
typedef struct { float x, y; } VFP(Vec2);
typedef struct { float x, y, z; } VFP(Vec3);
typedef struct { float x, y, z, a; } VFP(Vec4);

/* Vuili Color Type and Constants */
typedef struct { unsigned char r, g, b, a; } VFP(Color);
#define BLACK (VFP(Color)){ 0x00, 0x00, 0x00, 0x00 }
#define WHITE (VFP(Color)){ 0xFF, 0xFF, 0xFF, 0xFF }

/* Vuili Shape Types */
typedef struct { float x, y, width, height; } VFP(Rect);
typedef struct { VFP(Vec2) v1, v2, v3; } VFP(Tri);
typedef struct { float x1, y1, x2, y2; } VFP(Line);

typedef enum {
    //TODO:
    WINDOW_RESIZABLE    = 0x00000001ull,
    WINDOW_FULLSCREEN   = 0x00000002ull,
    FLAG_UNUSED00       = 0x00000004ull,
    FLAG_UNUSED01       = 0x00000008ull,
    FLAG_UNUSED02       = 0x00000010ull,
    FLAG_UNUSED03       = 0x00000020ull,
    FLAG_UNUSED04       = 0x00000040ull,
    FLAG_UNUSED05       = 0x00000080ull,
    FLAG_UNUSED06       = 0x00000100ull,
    FLAG_UNUSED07       = 0x00000200ull,
    FLAG_UNUSED08       = 0x00000400ull,
    FLAG_UNUSED09       = 0x00000800ull,
} VFP(WindowFlags);

//Key codes align with GLFW key codes
typedef enum {
    V_KEY_SPACE            = 32,
    V_KEY_APOSTROPHE       = 39, /* ' */
    V_KEY_COMMA            = 44, /* , */
    V_KEY_MINUS            = 45, /* - */
    V_KEY_PERIOD           = 46, /* . */
    V_KEY_SLASH            = 47, /* / */
    V_KEY_0                = 48,
    V_KEY_1                = 49,
    V_KEY_2                = 50,
    V_KEY_3                = 51,
    V_KEY_4                = 52,
    V_KEY_5                = 53,
    V_KEY_6                = 54,
    V_KEY_7                = 55,
    V_KEY_8                = 56,
    V_KEY_9                = 57,
    V_KEY_SEMICOLON        = 59, /* ; */
    V_KEY_EQUAL            = 61, /* = */
    V_KEY_A                = 65,
    V_KEY_B                = 66,
    V_KEY_C                = 67,
    V_KEY_D                = 68,
    V_KEY_E                = 69,
    V_KEY_F                = 70,
    V_KEY_G                = 71,
    V_KEY_H                = 72,
    V_KEY_I                = 73,
    V_KEY_J                = 74,
    V_KEY_K                = 75,
    V_KEY_L                = 76,
    V_KEY_M                = 77,
    V_KEY_N                = 78,
    V_KEY_O                = 79,
    V_KEY_P                = 80,
    V_KEY_Q                = 81,
    V_KEY_R                = 82,
    V_KEY_S                = 83,
    V_KEY_T                = 84,
    V_KEY_U                = 85,
    V_KEY_V                = 86,
    V_KEY_W                = 87,
    V_KEY_X                = 88,
    V_KEY_Y                = 89,
    V_KEY_Z                = 90,
    V_KEY_LEFT_BRACKET     = 91, /* [ */
    V_KEY_BACKSLASH        = 92, /* \ */
    V_KEY_RIGHT_BRACKET    = 93, /* ] */
    V_KEY_GRAVE_ACCENT     = 96, /* ` */
    V_KEY_WORLD_1          = 161, /* non-US #1 */
    V_KEY_WORLD_2          = 162, /* non-US #2 */

    /* Function keys */
    V_KEY_ESCAPE           = 256,
    V_KEY_ENTER            = 257,
    V_KEY_TAB              = 258,
    V_KEY_BACKSPACE        = 259,
    V_KEY_INSERT           = 260,
    V_KEY_DELETE           = 261,
    V_KEY_RIGHT            = 262,
    V_KEY_LEFT             = 263,
    V_KEY_DOWN             = 264,
    V_KEY_UP               = 265,
    V_KEY_PAGE_UP          = 266,
    V_KEY_PAGE_DOWN        = 267,
    V_KEY_HOME             = 268,
    V_KEY_END              = 269,
    V_KEY_CAPS_LOCK        = 280,
    V_KEY_SCROLL_LOCK      = 281,
    V_KEY_NUM_LOCK         = 282,
    V_KEY_PRINT_SCREEN     = 283,
    V_KEY_PAUSE            = 284,
    V_KEY_F1               = 290,
    V_KEY_F2               = 291,
    V_KEY_F3               = 292,
    V_KEY_F4               = 293,
    V_KEY_F5               = 294,
    V_KEY_F6               = 295,
    V_KEY_F7               = 296,
    V_KEY_F8               = 297,
    V_KEY_F9               = 298,
    V_KEY_F10              = 299,
    V_KEY_F11              = 300,
    V_KEY_F12              = 301,
    V_KEY_F13              = 302,
    V_KEY_F14              = 303,
    V_KEY_F15              = 304,
    V_KEY_F16              = 305,
    V_KEY_F17              = 306,
    V_KEY_F18              = 307,
    V_KEY_F19              = 308,
    V_KEY_F20              = 309,
    V_KEY_F21              = 310,
    V_KEY_F22              = 311,
    V_KEY_F23              = 312,
    V_KEY_F24              = 313,
    V_KEY_F25              = 314,
    V_KEY_KP_0             = 320,
    V_KEY_KP_1             = 321,
    V_KEY_KP_2             = 322,
    V_KEY_KP_3             = 323,
    V_KEY_KP_4             = 324,
    V_KEY_KP_5             = 325,
    V_KEY_KP_6             = 326,
    V_KEY_KP_7             = 327,
    V_KEY_KP_8             = 328,
    V_KEY_KP_9             = 329,
    V_KEY_KP_DECIMAL       = 330,
    V_KEY_KP_DIVIDE        = 331,
    V_KEY_KP_MULTIPLY      = 332,
    V_KEY_KP_SUBTRACT      = 333,
    V_KEY_KP_ADD           = 334,
    V_KEY_KP_ENTER         = 335,
    V_KEY_KP_EQUAL         = 336,
    V_KEY_LEFT_SHIFT       = 340,
    V_KEY_LEFT_CONTROL     = 341,
    V_KEY_LEFT_ALT         = 342,
    V_KEY_LEFT_SUPER       = 343,
    V_KEY_RIGHT_SHIFT      = 344,
    V_KEY_RIGHT_CONTROL    = 345,
    V_KEY_RIGHT_ALT        = 346,
    V_KEY_RIGHT_SUPER      = 347,
    V_KEY_MENU             = 348,
} KeyboardInput;

typedef enum {
    V_MOUSE_LEFT = 0,
    V_MOUSE_RIGHT = 1,
    V_MOUSE_MIDDLE = 2,

    V_MOUSE_BUTTON_1 = 0,
    V_MOUSE_BUTTON_2 = 1,
    V_MOUSE_BUTTON_3 = 2,
    V_MOUSE_BUTTON_4 = 3,
    V_MOUSE_BUTTON_5 = 4,
    V_MOUSE_BUTTON_6 = 5,
    V_MOUSE_BUTTON_7 = 6,
    V_MOUSE_BUTTON_8 = 7,
} MouseInput;

typedef enum {
    V_PRESSED,
    V_DOWN,
    V_RELEASED,
    V_UP,
} InputState;

#endif //_V_TYPES_H
