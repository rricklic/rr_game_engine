#ifndef RR_GAME_H
#define RR_GAME_H

#include "graphics/graphics_engine.h"
/*#include "core/game_layer.h"*/
#include "event/rr_event.h"
#include "room/rr_room.h"
#include "input/rr_input.h"
#include "timer/timer.h"
#include "types/dynamic_array.h"

/**
 * Controls the game based on the various game assets (objects, rooms, etc...)
 * 
 * 
 * 
 * 
 * 
 */ 

/**
 * TODO: to mimic slow motion, just arificially reduce frame rate
 */ 

typedef struct rr_game_t *rr_game_t;

/*
typedef struct rr_game_funcs_t {
    void (*on_create)(void);
    void (*on_event)(void);
    void (*on_step)(void);
    void (*on_render)(void);
    void (*on_destroy)(void);
    void (*on_userdef[10])(void);
} rr_game_funcs_t;
*/

rr_game_t
rr_game_create(
    int screen_width,
    int screen_height
    /*
    ,
    void (*init)(rr_game_t rr_game),
    void (*handle_input)(rr_game_t rr_game),
    void (*update)(rr_game_t rr_game, float dt),
    void (*render)(rr_game_t rr_game, float frame_percent)
    */);

/*
rr_game_t
rr_game_create2(
    int screen_width,
    int screen_height);
*/

/*
void
rr_game_add_layer(rr_game_t rr_game, game_layer_t *(*init_layer)());
*/

//TODO:
/*
void
rr_game_remove_layer(rr_game_t rr_game, game_layer_t *(*init_layer)());
*/

void
rr_game_event_subscribe(
    rr_game_t rr_game, 
    void *subscriber,
    rr_event_type_t rr_event_type, 
    int target_id, 
    void(*func)(void *data, void *event_data));

void
rr_game_destroy(rr_game_t rr_game);

void
rr_game_run(rr_game_t rr_game);

void
rr_game_run_start_room(rr_game_t rr_game, rr_room_t rr_room_start);

void
rr_game_goto_room(rr_game_t rr_game, rr_room_t rr_room);

/* TODO: REMOVE */
graphics_engine_t *
rr_game_get_graphics_engine(rr_game_t rr_game);

/* TODO: REMOVE */
rr_input_t
rr_game_get_input(rr_game_t rr_game);

void
rr_game_quit(rr_game_t rr_game);

#endif
