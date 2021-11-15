#ifndef RR_ROOM_H
#define RR_ROOM_H

#include "object/rr_object.h"
#include "physics/vector_2d.h"
#include "types/types_basic.h"
#include "types/rr_array.h"
#include "graphics/renderer.h"
#include "input/rr_input.h"
#include "event/rr_event_system.h"

/*
    Like a level, space where resources (e.g.: objects) will be placed

    width, height
    layers - contain/hold resources (e.g.: objects)
       instances layers - objects
       background layers - sprite/color (can be tiled)
       tile layers -
       path layers - 
       asset layers -
*/

typedef struct rr_room_layer_t *rr_room_layer_t;
struct rr_room_layer_t {
    rr_array_t objects; /* rr_array(rr_object) */
    void *data;
};

typedef struct rr_room_t *rr_room_t;
struct rr_room_t {
    char *name; /* TODO: id */
    uint_t width;
    uint_t height;
    rr_array_t room_layers; /* rr_array(rr_room_layer_t) */
    void (*on_create)(rr_room_t rr_room, rr_event_system_t rr_event_system);
    /* void (*on_event)(rr_room_t rr_room); */
    void (*on_step)(rr_room_t rr_room, rr_input_t rr_input, float_t dt);
    void (*on_draw)(rr_room_t rr_room, renderer_t *rr_renderer, float_t frame_percent);
    void (*on_destroy)(rr_room_t rr_room);
    /* void (*on_userdef[10])(rr_room_t rr_room); */
};


rr_room_t
rr_room_create(uint_t width, uint_t height);

rr_room_t
rr_room_create_full(
    uint_t width,
    uint_t height,
    void (*on_create)(rr_room_t rr_room, rr_event_system_t rr_event_system),
    void (*on_step)(rr_room_t rr_room, rr_input_t rr_input, float_t dt),
    void (*on_draw)(rr_room_t rr_room, renderer_t *rr_renderer, float_t frame_percent),
    void (*on_destroy)(rr_room_t rr_room));

void
rr_room_set_on_create(rr_room_t rr_room, void (*func)(rr_room_t rr_room, rr_event_system_t rr_event_system));

void
rr_room_set_on_step(rr_room_t rr_room, void (*func)(rr_room_t rr_room, rr_input_t rr_input, float_t dt));

void
rr_room_set_on_draw(rr_room_t rr_room, void (*func)(rr_room_t rr_room, renderer_t *rr_renderer, float_t frame_percent));

void
rr_room_set_on_destroy(rr_room_t rr_room, void (*func)(rr_room_t rr_room));

int
rr_room_add_layer(rr_room_t rr_room, rr_room_layer_t rr_room_layer);

void
rr_room_destroy(rr_room_t rr_room);

#endif
