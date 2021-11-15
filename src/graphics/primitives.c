#include "graphics/primitives.h"
#include "graphics/renderer.h"
#include "types/rect.h"
#include "types/types_basic.h"

inline void
primatives_rect(renderer_t *renderer, float_t x, float_t y, uint_t w, uint_t h, float_t camera_x, float_t camera_y, byte_t color[4])
{
    rect_t rect = {x - camera_x, y - camera_y, w, h};
    render_draw_color(renderer, color[0], color[1], color[2], color[3]);
    render_draw_rect(renderer, &rect);    
}

inline void
primatives_fill_rect(renderer_t *renderer, float_t x, float_t y, uint_t w, uint_t h, float_t camera_x, float_t camera_y, byte_t color[4])
{
    rect_t rect = {x - camera_x, y - camera_y, w, h};
    render_draw_color(renderer, color[0], color[1], color[2], color[3]);
    render_fill_rect(renderer, &rect);    
}

inline void
primatives_line(renderer_t *renderer, float_t x1, float_t y1, float_t x2, float_t y2, float_t camera_x, float_t camera_y, byte_t color[4])
{
    render_draw_color(renderer, color[0], color[1], color[2], color[3]);
    render_draw_line(renderer, x1 - camera_x, y1 - camera_y, x2 - camera_x, y2 - camera_y);
}

inline void
primatives_point(renderer_t *renderer, float_t x, float_t y, float_t camera_x, float_t camera_y, byte_t color[4])
{
    render_draw_color(renderer, color[0], color[1], color[2], color[3]);
    render_draw_point(renderer, x - camera_x, y - camera_y);
}
