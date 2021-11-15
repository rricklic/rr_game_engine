#ifndef RR_TEXTURE_MANAGER_H
#define RR_TEXTURE_MANAGER_H

#include "graphics/renderer.h"
#include "types/types_basic.h"

typedef struct texture_manager_t {
    void *impl;
} texture_manager_t;

void
texture_manager_free(texture_manager_t *texture_manager);

texture_manager_t *
texture_manager_create(void);

void
texture_manager_add(texture_manager_t *texture_manager, renderer_t *renderer, char *id, char *pathname);

void
texture_manager_remove(texture_manager_t *texture_manager, char *id);

void
texture_manager_render(
    texture_manager_t *texture_manager, 
    renderer_t *renderer, 
    char *id, 
    sint_t x,
    sint_t y, 
    uint_t w, 
    uint_t h,
    sint_t camera_x,
    sint_t camera_y);

void
texture_manager_render_ex(
    texture_manager_t *texture_manager, 
    renderer_t *renderer, 
    char *id, 
    float_t x, 
    float_t y, 
    uint_t w, 
    uint_t h, 
    float_t rotation, 
    renderer_flip_t flip_mode);

void
texture_manager_render_frame(
    texture_manager_t *texture_manager, 
    renderer_t *renderer, 
    char *id, 
    float_t x,
    float_t y,
    uint_t w,
    uint_t h,
    byte_t frame,
    byte_t row);

void
texture_manager_render_frame_ex(
    texture_manager_t *texture_manager, 
    renderer_t *renderer, 
    char *id, 
    float_t x,
    float_t y,
    uint_t w,
    uint_t h,
    byte_t frame, 
    byte_t row,
    float_t rotation,
    renderer_flip_t flip_mode,
    float_t camera_x,
    float_t camera_y);

#endif