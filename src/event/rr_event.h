#ifndef RR_GAME_EVENT_H
#define RR_GAME_EVENT_H

#include "types/types_basic.h"

/*
typedef enum rr_event_t {
    on_create = 0,
    on_destroy,
    on_cleanup,
    on_step,
    on_alarm,
    on_draw,
    on_mouse,
    on_key_down,
    on_key_pressed,
    on_key_up,
    on_collision,
    on_outside_room,
    on_intersect_boundry,
    on_game_start,
    on_game_end,
    on_room_start,
    on_room_end,
    on_animation_start,
    on_animation_end,
    on_animation_update,
    on_path_start,
    on_path_end,
    on_user_event
} rr_event_t;
*/

typedef enum rr_event_type_t {
    rr_event_type_none = 0,
    /* window */
    rr_event_type_window_close,
    rr_event_type_window_resize,
    rr_event_type_window_move,
    /* keyboard */
    rr_event_type_key_down,
    rr_event_type_key_up,
    rr_event_type_key_pressed,
    rr_event_type_key_released,    
    /* mouse */
    rr_event_type_mouse_button_pressed,
    rr_event_type_mouse_button_down,
    rr_event_type_mouse_button_up,
    rr_event_type_mouse_moved,
    rr_event_type_mouse_scroll,
    /* create */
    rr_event_type_create,
    /* destroy */
    rr_event_type_destroy,
    /* cleanup */
    rr_event_type_cleanup,
    /* step */
    rr_event_type_step,
    /* alarm */
    rr_event_type_alarm,
    /* draw */
    rr_event_type_draw,
    /* collision */
    rr_event_type_collision,
    /* other */
    rr_event_type_other,
    /* asynchronous */
    rr_event_type_asynchronous,

} rr_event_type_t;

typedef enum rr_event_category_t {
    rr_event_category_none = 0,
    rr_event_category_window,
    rr_event_category_input,
    rr_event_category_keyboard,
    rr_event_category_mouse
} rr_event_category_t;

typedef struct rr_keyboard_event_t {
    int key_code;
    rr_event_type_t rr_event_type;
} rr_keyboard_event_t;

/*
typedef struct rr_event_header_t {
    rr_event_type_t rr_event_type;
    rr_event_category_t rr_event_category;
    int is_handled;
} rr_event_header_t;

typedef struct rr_event_keyboard_t {
    rr_event_header_t header;
    int key_code;
} rr_event_keyboard_t;

typedef struct rr_event_mouse_t {
    rr_event_header_t header;
    float_t x;
    float_t y;
    int button;
} rr_event_mouse_t;

typedef struct rr_event_window_t {
    rr_event_header_t header;
} rr_event_window_t;
*/
/* TODO: union */
/*
typedef struct rr_event_t {
    rr_event_header_t header;
} rr_event_t;
*/

/*
rr_event_t *
rr_event_create();

rr_event_t *
rr_event_destroy();
*/

#endif