#include "core/rr_game.h"
#include "core/game_layer.h"
#include "graphics/graphics_engine.h"
#include "graphics/text_renderer.h"
#include "input/rr_input.h"
#include "timer/timer.h"
#include "event/rr_event_system.h"
#include "types/types_basic.h"

/* TODO: dialog text at different speed */

#define MAX_DT 0.25f
#define DT_STEP 0.01f

/* TODO: pass in target FPS; use to control rendering */
#define SCREEN_FPS 60
#define SCREEN_TICKS_PER_FRAME 1000.f / SCREEN_FPS

struct rr_game_t {
    int is_running;
    uint_t fps;
    graphics_engine_t *graphics_engine;
    ticktimer_t *timer;
    rr_input_t rr_input;
    rr_event_system_t rr_event_system;
    rr_room_t rr_room;
};

/*
TODO: handle_input/update fixed time step (20 times per second)
      render capped at 60 fps; ability to render at different framerates
*/

static void
rr_game_on_room_create(rr_game_t rr_game)
{
    rr_game->rr_room->on_create(rr_game->rr_room, rr_game->rr_event_system);
}

static void
rr_game_on_room_step(rr_game_t rr_game, float_t dt)
{
    rr_game->rr_room->on_step(rr_game->rr_room, rr_game->rr_input, dt);
}

static void
rr_game_on_room_draw(rr_game_t rr_game, float_t frame_percent)
{
    rr_game->rr_room->on_draw(rr_game->rr_room, rr_game->graphics_engine->renderer, frame_percent);
}

static void
rr_game_on_room_destroy(rr_game_t rr_game)
{
    rr_game->rr_room->on_destroy(rr_game->rr_room);
}

void
rr_game_destroy(rr_game_t rr_game)
{
    if (rr_game) {
        rr_game_on_room_destroy(rr_game);

        timer_destroy(rr_game->timer);
        rr_input_destroy(rr_game->rr_input);
        graphics_engine_destroy(rr_game->graphics_engine);
        free(rr_game);
    }
}

static void
rr_game_event_handler(rr_game_t rr_game)
{
    rr_event_system_handle_events(rr_game->rr_event_system);
}

void
rr_game_event_subscribe(
    rr_game_t rr_game, 
    void *subscriber,
    rr_event_type_t rr_event_type, 
    int target_id, 
    void(*func)(void *data, void *event_data))
{
    rr_event_system_subscribe(rr_game->rr_event_system, subscriber, rr_event_type, target_id, func);
}

static void
rr_game_handle_input(rr_game_t rr_game)
{
    rr_input_fetch_state(rr_game->rr_input);

    rr_keyboard_event_t *rr_keyboard_event;

    int keys[] = {RR_KEYBOARD_UP, RR_KEYBOARD_DOWN, RR_KEYBOARD_LEFT, RR_KEYBOARD_RIGHT}; /* TODO: get from subscriptions (see rr_game_event_subscribe) */
    for (int index = 0; index < 4; index++) {

        if (rr_input_is_key_pressed(rr_game->rr_input, keys[index])) {
            printf("rr_input_is_key_pressed = %d\n", keys[index]);
            rr_keyboard_event = malloc(sizeof(*rr_keyboard_event)); /* TODO: MAKE SURE THIS IS NOT A MEMORY LEAK; HAVE RR_EVENT_SYSTEM FREE UP EVENT DATA!!!! */
            if (rr_keyboard_event != NULL) {
                rr_keyboard_event->key_code = keys[index];
                rr_keyboard_event->rr_event_type = rr_event_type_key_pressed;
                rr_event_system_notify(rr_game->rr_event_system, rr_event_type_key_pressed, keys[index], rr_keyboard_event);
            }
        }
        if (rr_input_is_key_down(rr_game->rr_input, keys[index])) {
            printf("rr_input_is_key_down = %d\n", keys[index]);
            rr_keyboard_event = malloc(sizeof(*rr_keyboard_event));
            if (rr_keyboard_event != NULL) {
                rr_keyboard_event->key_code = keys[index];
                rr_keyboard_event->rr_event_type = rr_event_type_key_down;            
                rr_event_system_notify(rr_game->rr_event_system, rr_event_type_key_down, keys[index], rr_keyboard_event);
            }
        }
        if (rr_input_is_key_released(rr_game->rr_input, keys[index])) {
            printf("rr_input_is_key_released = %d\n", keys[index]);
            rr_keyboard_event = malloc(sizeof(*rr_keyboard_event));
            if (rr_keyboard_event != NULL) {
                rr_keyboard_event->key_code = keys[index];
                rr_keyboard_event->rr_event_type = rr_event_type_key_released;                        
                rr_event_system_notify(rr_game->rr_event_system, rr_event_type_key_released, keys[index], rr_keyboard_event);
            }
        }
        if (rr_input_is_key_up(rr_game->rr_input, keys[index])) {
            //printf("rr_input_is_key_up = %d\n", keys[index]);
            rr_keyboard_event = malloc(sizeof(*rr_keyboard_event));
            if (rr_keyboard_event != NULL) {
                rr_keyboard_event->key_code = keys[index];
                rr_keyboard_event->rr_event_type = rr_event_type_key_up;
                rr_event_system_notify(rr_game->rr_event_system, rr_event_type_key_up, keys[index], rr_keyboard_event);
            }
        }
    }

    if (rr_input_is_quit(rr_game->rr_input)) {
        rr_game->is_running = 0;
        return;
    }
}

rr_game_t
rr_game_create(int screen_width, int screen_height)
{
    rr_game_t rr_game;

    rr_game = malloc(sizeof(*rr_game));
    if (rr_game == NULL) {
        printf("Unable to allocate rr_game\n");
        return NULL;
    }

    rr_game->graphics_engine = graphics_engine_create(screen_width, screen_height);
    if (rr_game->graphics_engine == NULL) {
        printf("Unable to allocate graphics_engine\n");
        rr_game_destroy(rr_game);
        return NULL;
    }

    rr_game->timer = ticktimer_create();
    if (rr_game->timer == NULL) {
        printf("Unable to allocate rr_game_timer\n");
        rr_game_destroy(rr_game);
        return NULL;
    }

    rr_game->rr_input = rr_input_create();
    if (rr_game->rr_input == NULL) {
        printf("Unable to allocate rr_input\n");
        rr_game_destroy(rr_game);
        return NULL;
    }

    rr_game->rr_event_system = rr_event_system_create();
    if (rr_game->rr_event_system == NULL) {
        printf("Unable to allocate rr_event_system\n");
        rr_game_destroy(rr_game);
        return NULL;
    }

    /* TODO: move to rr_game_run */
    rr_game->is_running = 1;

    return rr_game;
}

static float_t
rr_game_calc_dt(ticktimer_t *timer)
{
    float_t dt = timer_calculate_ticks(timer) / 1000.f;
    timer_start(timer);
    return dt;
}

/*
    1. calc dt
    2. handle input
    3. step
    4. draw
*/
void
rr_game_run(rr_game_t rr_game)
{
    float_t dt;
    float_t dt_accumulator = 0.f;
    float_t frame_percent;

    rr_game_on_room_create(rr_game);

    while (rr_game->is_running) {
        dt = rr_game_calc_dt(rr_game->timer);
        if (dt > MAX_DT) {
            dt = MAX_DT;
        }
        dt_accumulator += dt;

        while (dt_accumulator >= DT_STEP) {
            /* TODO: previous_state = current_state */
            rr_game_handle_input(rr_game);
            rr_event_system_handle_events(rr_game->rr_event_system);
            rr_game_on_room_step(rr_game, DT_STEP);
            dt_accumulator -= DT_STEP;
        }
        
        frame_percent = dt_accumulator / DT_STEP;

        render_clear_color(rr_game->graphics_engine->renderer, COLOR_BLACK);
        rr_game_on_room_draw(rr_game, frame_percent);

        render_show(rr_game->graphics_engine->renderer);
    }
}

void
rr_game_run_start_room(rr_game_t rr_game, rr_room_t rr_room_start)
{
    rr_game->rr_room = rr_room_start;
    rr_game_run(rr_game);
}

void
rr_game_goto_room(rr_game_t rr_game, rr_room_t rr_room)
{
    rr_game_on_room_destroy(rr_game);
    rr_game->rr_room = rr_room;
    rr_game_on_room_create(rr_game);
}

/* TODO: REMOVE */
graphics_engine_t *
rr_game_get_graphics_engine(rr_game_t rr_game)
{
    return rr_game->graphics_engine;
}

/* TODO: REMOVE */
rr_input_t
rr_game_get_input(rr_game_t rr_game)
{
    return rr_game->rr_input;
}

/* TODO: REMOVE */
void
rr_game_quit(rr_game_t rr_game)
{
    rr_game->is_running = 0;
}