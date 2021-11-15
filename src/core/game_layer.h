#ifndef RR_GAME_LAYER_H
#define RR_GAME_LAYER_H

#ifdef DO_NOT_COMPILE

#include "types/types_basic.h"
//#include "core/game_engine.h"
#include "event/rr_event.h"

typedef struct game_layer_t {
    void *data;
    struct game_layer_t *(*init)();
    void (*on_create)(struct game_layer_t *game_layer);
    void (*update)(struct game_layer_t *game_layer, float_t dt);
    void (*handle_event)(struct game_layer_t *game_layer/*, rr_event_t *event*/);
    void (*render)(struct game_engine_t *game_engine, struct game_layer_t *game_layer);
    void (*on_destroy)(struct game_layer_t *game_layer);
} game_layer_t;

#endif

#endif