#ifndef RR_OBJECT_H
#define RR_OBJECT_H

#include "physics/vector_2d.h"
#include "sprite/rr_sprite.h"
#include "types/types_basic.h"

/*
   properties
   behavior - event -> action (if this then that) [SEE event/rr_event.h]
*/

typedef struct rr_object_t {
    uint_t rr_object_id; // Note: will be the same for all instances of this object
    /* uint_t object_type; */ /* Maybe? */
    vector_2d_t position;
    float_t rotation; /* 0 = right, 90 = up, 180 = left, 270 = down */
    float_t direction;
    float_t speed; // TODO: do we need max_speed?
    float_t alpha;
    rr_sprite_t *rr_sprite; /*TODO: uint_t rr_sprite_id;*/
} rr_object_t;

rr_object_t *
rr_object_create(float_t x, float_t y);

/* TODO: add "step events" (e.g.: rr_object_funcs) to an object which will be called for each game step */

void 
rr_object_destroy(rr_object_t *rr_object);

#endif