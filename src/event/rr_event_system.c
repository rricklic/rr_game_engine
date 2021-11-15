#include <stddef.h>

#include "rr_event_system.h"
#include "rr_event.h"
#include "types/rr_map.h"

typedef struct rr_event_t {
    rr_event_type_t rr_event_type;
    /*rr_event_category_t rr_event_category;*/
    int target_id;
    void *event_data;
} rr_event_t;

typedef struct rr_event_callback_t {
    void *subscriber;
    void (*func)(void *subscriber, void *data);
} rr_event_callback_t;

struct rr_event_system_t {
    rr_map_t event_callback_map; /* rr_event_t => rr_array(rr_event_callback_t) */
    rr_array_t events; /* rr_array_t(rr_event_t) TODO: make a set, so that the event only triggers once even if it was notified multiple times */
};

static int
rr_event_hash_func(rr_event_t *rr_event)
{
    if (rr_event == NULL) {
        return 0;
    }
    unsigned int hash = 7;
    hash = 31 * hash + rr_event->rr_event_type;
    hash = 31 * hash + rr_event->target_id;
    return hash;
}

static int
rr_event_equal_func(rr_event_t *rr_event_1, rr_event_t *rr_event_2)
{
    if (rr_event_1 == NULL || rr_event_2 == NULL) {
        return 0;
    }
    return rr_event_1->rr_event_type == rr_event_2->rr_event_type && rr_event_1->target_id == rr_event_2->target_id;
}

rr_event_system_t
rr_event_system_create(void)
{
    rr_event_system_t rr_event_system;
    rr_event_system = malloc(sizeof(*rr_event_system));
    if (rr_event_system == NULL) {
        return NULL;
    }

    /* TODO: event_callback_map needs a comparator function; destroy key/value function */
    rr_event_system->event_callback_map = rr_map_create_full(rr_event_hash_func, rr_event_equal_func, NULL, NULL);
    if (rr_event_system->event_callback_map == NULL) {
        free(rr_event_system);
        return NULL;
    }

    /* TODO: event_map needs a comparator function; destroy key/value function */
    rr_event_system->events = rr_array_create(sizeof(rr_event_t *));
    if (rr_event_system->events == NULL) {
        free(rr_event_system->event_callback_map);
        free(rr_event_system);
        return NULL;
    }    

    return rr_event_system;
}

void *
rr_event_system_subscribe(
    rr_event_system_t rr_event_system, /* rr_event_category_t rr_event_category, */
    void *subscriber,
    rr_event_type_t rr_event_type, 
    int target_id, 
    void(*func)(void *data, void *event_data))
{
    rr_event_t *rr_event;
    rr_event = malloc(sizeof(*rr_event));
    if (rr_event == NULL) {
        return NULL;
    }

    rr_event_callback_t *rr_event_callback;
    rr_event_callback = malloc(sizeof(*rr_event_callback));
    if (rr_event_callback == NULL) {
        free(rr_event);
        return NULL;
    }

    rr_event->rr_event_type = rr_event_type;
    rr_event->target_id = target_id;
    rr_event->event_data = NULL;

    rr_event_callback->subscriber = subscriber;
    rr_event_callback->func = func;

    /* TODO: rr_array should be a set: needs a comparator function */
    rr_array_t rr_array = rr_map_get(rr_event_system->event_callback_map, rr_event);
    if (rr_array == NULL) {
        rr_array = rr_array_create(sizeof(*rr_event_callback));
    }
    rr_array_append(rr_array, rr_event_callback);
    rr_map_put(rr_event_system->event_callback_map, rr_event, rr_array);
}

void
rr_event_system_notify(rr_event_system_t rr_event_system, rr_event_type_t rr_event_type, int target_id, void *event_data)
{
    rr_event_t *rr_event;
    rr_event = malloc(sizeof(*rr_event));
    if (rr_event == NULL) {
        return;
    }

    rr_event->rr_event_type = rr_event_type;
    rr_event->target_id = target_id;
    rr_event->event_data = event_data;

    rr_array_append(rr_event_system->events, rr_event);
}

static void
rr_event_system_call_event_callback(rr_event_callback_t *rr_event_callback, rr_event_t *rr_event)
{
    rr_event_callback->func(rr_event_callback->subscriber, rr_event->event_data);
}

static void
rr_event_system_handle_event(rr_event_t *rr_event, rr_event_system_t rr_event_system)
{
    rr_array_t rr_event_callbacks = rr_map_get(rr_event_system->event_callback_map, rr_event);
    if (rr_event_callbacks != NULL) {
        rr_array_foreach(rr_event_callbacks, rr_event_system_call_event_callback, rr_event);
    }
}

void
rr_event_system_handle_events(rr_event_system_t rr_event_system)
{
    rr_array_foreach(rr_event_system->events, rr_event_system_handle_event, rr_event_system);
    rr_array_clear(rr_event_system->events);
}

void
rr_event_system_destroy(rr_event_system_t rr_event_system)
{
    if (rr_event_system) {
        rr_map_destroy(rr_event_system->event_callback_map);
        free(rr_event_system);
    }
}