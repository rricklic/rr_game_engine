#ifndef RR_OBJECT_FUNC
#define RR_OBJECT_FUNC

#include "rr_object.h"

/* TODO: make inline; no depends */

void
rr_object_func_move_wrap(rr_object_t rr_object, uint_t rr_room_width, uint_t rr_room_height);

void
rr_object_func_move_bounce(rr_object_t rr_object, uint_t rr_room_width, uint_t rr_room_height);

int
rr_object_func_is_outside(rr_object_t rr_object, uint_t rr_room_width, uint_t rr_room_height);

#endif