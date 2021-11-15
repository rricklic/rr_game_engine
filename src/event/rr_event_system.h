#ifndef RR_EVENT_SYSTEM_H
#define RR_EVENT_SYSTEM_H

#include "event/rr_event.h"
#include "types/rr_map.h"
#include "types/rr_array.h"

typedef struct rr_event_system_t *rr_event_system_t;

rr_event_system_t
rr_event_system_create(void);

void *
rr_event_system_subscribe(
    rr_event_system_t rr_event_system, /* rr_event_category_t rr_event_category, */
    void *subscriber,
    rr_event_type_t rr_event_type, 
    int target_id, 
    void(*func)(void *data, void *event_data)
);

void
rr_event_system_notify(rr_event_system_t rr_event_system, rr_event_type_t rr_event_type, int target_id, void *event_data);

void
rr_event_system_handle_events(rr_event_system_t rr_event_system);

void
rr_event_system_destroy(rr_event_system_t rr_event_system);

#endif