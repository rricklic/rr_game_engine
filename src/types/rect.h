#ifndef RR_RECT_H
#define RR_RECT_H

#define SDL_GAME_ENGINE /* TODO: place elsewhere OR determine somehow */

#ifdef SDL_GAME_ENGINE
#include <SDL.h>
typedef struct SDL_Rect rect_t;
#else
#include "../types/types_basic.h"
typedef struct rect_t {
    sint_t x;
    sint_t y;
    uint_t w;
    uint_t h;
} rect_t;
#endif

#define RECT_UPPER_LEFT(r) (vector_2d_t){r.x, r.y}
#define RECT_UPPER_RIGHT(r) (vector_2d_t){(r.x + r.w), r.y}
#define RECT_LOWER_RIGHT(r) (vector_2d_t){(r.x + r.w), (r.y + r.h)}
#define RECT_LOWER_LEFT(r) (vector_2d_t){r.x, (r.y + r.h)}

#endif