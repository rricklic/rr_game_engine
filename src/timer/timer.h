#ifndef RR_TIMER_H
#define RR_TIMER_H

#include "types/types_basic.h"

typedef struct ticktimer_t {
    uint_t start_time;
    uint_t pause_time;
    int is_paused;
} ticktimer_t;

void
timer_destroy(ticktimer_t *timer);

ticktimer_t *
ticktimer_create();

void
timer_start(ticktimer_t *timer);

void
timer_toggle_pause(ticktimer_t *timer);

uint_t
timer_calculate_ticks(ticktimer_t *timer);

#endif
