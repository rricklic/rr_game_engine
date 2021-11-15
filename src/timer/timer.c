#include <SDL_timer.h>

#include "timer/timer.h"
#include "types/types_basic.h"

#define get_ticks SDL_GetTicks
/* #define get_ticks2() SDL_GetPerformanceCounter(); */

void
timer_destroy(ticktimer_t *timer)
{
    free(timer);
}

ticktimer_t *
ticktimer_create()
{
    ticktimer_t *timer = NULL;
    timer = (ticktimer_t *)malloc(sizeof(ticktimer_t));
    if (!timer) {
        return NULL;
    }

    timer->start_time = get_ticks();
    timer->pause_time = 0;
    timer->is_paused = 0;
    return timer;
}

void
timer_start(ticktimer_t *timer)
{
    timer->start_time = get_ticks();
    timer->pause_time = 0;
    timer->is_paused = 0;
}

void
timer_toggle_pause(ticktimer_t *timer)
{
    if (!timer->is_paused) {
        timer->pause_time = get_ticks() - timer->start_time;
        timer->start_time = 0;
    } else if (timer->is_paused) {
        timer->start_time = get_ticks() - timer->pause_time;
        timer->pause_time = 0;
    }

    timer->is_paused = !timer->is_paused;
}

uint_t
timer_calculate_ticks(ticktimer_t *timer)
{
    return timer->is_paused ? timer->pause_time : get_ticks() - timer->start_time;
}

#undef get_ticks
