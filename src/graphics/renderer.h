#ifndef RR_RENDERER_H
#define RR_RENDERER_H

#include <SDL_render.h> // TODO: use define

#include <GL/gl.h> /* TODO: hide behind interface */

#include "types/types_basic.h"

typedef SDL_Renderer renderer_t;
typedef SDL_RendererFlip renderer_flip_t;

/* TODO: look into sdl_gpu */ 
/* TODO: batch rendering: limit draw pools */

/* TODO: good idea, or bad... */
typedef struct color_t {
    byte_t r;
    byte_t g;
    byte_t b;
    byte_t a;
} color_t;

typedef color_t rr_rgba_t;

#define COLOR_RED (byte_t[4]){0xFF, 0x00, 0x00, 0xFF}
#define COLOR_ORANGE (byte_t[4]){0xFF, 0xA5, 0x00, 0xFF}
#define COLOR_YELLOW (byte_t[4]){0xFF, 0xFF, 0x00, 0xFF}
#define COLOR_GREEN (byte_t[4]){0x00, 0xFF, 0x00, 0xFF}
#define COLOR_BLUE (byte_t[4]){0x00, 0x00, 0xFF, 0xFF}
#define COLOR_PURPLE (byte_t[4]){0x6A, 0x0D, 0xAD, 0xFF}
#define COLOR_BLACK (byte_t[4]){0x00, 0x00, 0x00, 0xFF}
#define COLOR_WHITE (byte_t[4]){0xFF, 0xFF, 0xFF, 0xFF}
#define COLOR_GREY (byte_t[4]){0xAA, 0xAA, 0xAA, 0xFF}

/*TODO: #ifdef SDL2 */

#define renderer_flip_none SDL_FLIP_NONE
#define renderer_flip_horizontal SDL_FLIP_HORIZONTAL

#define texture_destroy(t) SDL_DestroyTexture(t)
#define surface_free(s) SDL_FreeSurface(s)

#define renderer_create(w, i, o) SDL_CreateRenderer(w, i, o)
#define renderer_destroy(r) SDL_DestroyRenderer(r)
#define render_create_texture_from_surface(r, s) SDL_CreateTextureFromSurface(r, s)
#define render_copy(r, t, s, d) SDL_RenderCopy(r, t, s, d)
#define render_copy_ex(r, t, s, d, R, N, f) SDL_RenderCopyEx(r, t, s, d, R, N, f)
#define render_draw_color(r, c0, c1, c2, c3) SDL_SetRenderDrawColor(r, c0, c1, c2, c3)
#define render_draw_rect(r, R) SDL_RenderDrawRect(r, R)
#define render_fill_rect(r, R) SDL_RenderFillRect(r, R)
#define render_draw_line(r, x1, y1, x2, y2) SDL_RenderDrawLine(r, x1, y1, x2, y2)
#define render_draw_point(r, x, y) SDL_RenderDrawPoint(r, x, y);
#define render_clear(r) SDL_RenderClear(r)
#define render_clear_color(r, c) SDL_SetRenderDrawColor(r, c[0], c[1], c[2], c[3]); SDL_RenderClear(r) /* TODO: enforce c is 4 index array */
#define render_set_scale(r, z) SDL_RenderSetScale(r, z, z)
#define render_show(r) SDL_RenderPresent(r)

static inline void
render_rotate(float_t x, float_t y, float_t degrees)
{
    glPopMatrix();
    glPushMatrix();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    /* Center screen, rotate, return screen to original position */
    glTranslatef(
        x /* -x_offset */, // TODO: rotation offset make for curvy erratic movement
        y /* -y_offset */, 
        0.f);
    glRotatef(degrees, 0.f, 0.f, 1.f);
    glTranslatef(-x /* -x_offset */, -y /* -y_offset */, 0.f);
}

static inline void
render_rotate_reset()
{
    glPopMatrix();
    glPushMatrix();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

#endif
