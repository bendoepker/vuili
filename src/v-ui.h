#ifndef _V_UI_H
#define _V_UI_H

#include <vuili.h>

/* UI Components */

typedef struct {
    V_Rect hitbox;
    bool clicked;
    bool hovered;
} V_ButtonBase;

typedef struct {
    V_ButtonBase base;
    V_Texture texture;
} V_ImageButton;

#endif //_V_UI_H
