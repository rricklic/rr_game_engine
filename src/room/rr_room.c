#include "room/rr_room.h"
#include "types/rr_array.h"

/* TODO: REMOVE */
rr_room_t
rr_room_create(uint_t width, uint_t height)
{
    rr_room_t rr_room;
    rr_room = malloc(sizeof(*rr_room));
    if (rr_room == NULL) {
        return NULL;
    }

    rr_room->width = width;
    rr_room->height = height;
    rr_room->room_layers = rr_array_create(sizeof(rr_room_layer_t));
}

rr_room_t
rr_room_create_full(
    uint_t width,
    uint_t height,
    void (*on_create)(rr_room_t rr_room, rr_event_system_t rr_event_system),
    void (*on_step)(rr_room_t rr_room, rr_input_t rr_input, float_t dt),
    void (*on_draw)(rr_room_t rr_room, renderer_t *rr_renderer, float_t frame_percent),
    void (*on_destroy)(rr_room_t rr_room))
{
    rr_room_t rr_room;
    rr_room = malloc(sizeof(*rr_room));
    if (rr_room == NULL) {
        return NULL;
    }

    rr_room->width = width;
    rr_room->height = height;
    rr_room->room_layers = rr_array_create(sizeof(rr_room_layer_t));
    rr_room->on_create = on_create;
    rr_room->on_step = on_step;
    rr_room->on_draw = on_draw;
    rr_room->on_destroy = on_destroy;
}

void
rr_room_set_on_create(rr_room_t rr_room, void (*func)(rr_room_t rr_room, rr_event_system_t rr_event_system))
{
    rr_room->on_create = func;
}

void
rr_room_set_on_step(rr_room_t rr_room, void (*func)(rr_room_t rr_room, rr_input_t rr_input, float_t frame_percent))
{
    rr_room->on_step = func;
}

void
rr_room_set_on_draw(rr_room_t rr_room, void (*func)(rr_room_t rr_room, renderer_t *renderer, float_t dt))
{
    rr_room->on_draw = func;
}

void
rr_room_set_on_destroy(rr_room_t rr_room, void (*func)(rr_room_t rr_room))
{
    rr_room->on_destroy = func;
}

int
rr_room_add_layer(rr_room_t rr_room, rr_room_layer_t rr_room_layer)
{
    rr_array_append(rr_room->room_layers, rr_room_layer);
    return rr_array_get_length(rr_room->room_layers);
}

void
rr_room_remove_layer(rr_room_t rr_room, int rr_room_layer_id)
{
    rr_array_remove_index(rr_room->room_layers, rr_room_layer_id);
}

void
rr_room_destroy(rr_room_t rr_room)
{
    if (rr_room) {
        rr_array_destroy(rr_room->room_layers);
        free(rr_room);
    }
}