#ifndef RR_SPRITE_H
#define RR_SPRITE_H

//#include "physics/vector_2d.h"
#include "types/types_basic.h"
#include "graphics/rr_texture.h"

/*
Any image which will be in game
  - size (e.g.: 32x32)
  - origin - point where the image would rotate (e.g.: center)
  - can have animation (frames, speed)

*/

/* TODO: make opaque-type */
typedef struct rr_sprite_t {
    uint_t id;
    //vector_2d_t size;
    //vector_2d_t origin;
    uint_t width;
    uint_t height;
    uint_t origin_x;
    uint_t origin_y;

    /* TODO: texture_t or texture_id? */
    texture_t *texture; /*uint_t texture_id;*/
    
} rr_sprite_t;

rr_sprite_t *
rr_sprite_create(uint_t width, uint_t height, uint_t origin_x, uint_t origin_y, texture_t *texture);

void
rr_sprite_destroy(rr_sprite_t *rr_sprite);

#endif