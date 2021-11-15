#ifndef RR_PRIMATIVES_H
#define RR_PRIMATIVES_H

#include "graphics/renderer.h"
#include "types/types_basic.h"

void
primatives_rect(renderer_t *renderer, float_t x, float_t y, uint_t w, uint_t h, float_t camera_x, float_t camera_y, byte_t color[4]);

void
primatives_fill_rect(renderer_t *renderer, float_t x, float_t y, uint_t w, uint_t h, float_t camera_x, float_t camera_y, byte_t color[4]);

void
primatives_line(renderer_t *renderer, float_t x1, float_t y1, float_t x2, float_t y2, float_t camera_x, float_t camera_y, byte_t color[4]);

void
primatives_point(renderer_t *renderer, float_t x, float_t y, float_t camera_x, float_t camera_y, byte_t color[4]);

#endif