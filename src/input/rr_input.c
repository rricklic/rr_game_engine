#include <SDL_events.h>

#include "input/rr_input.h"

#define RR_INPUT_NUM_KEYS 256

struct rr_input_t {
    int is_quit;
    unsigned int num_keys;
    byte_t *key_states;
    byte_t *prev_key_states;
    uint_t mouse_state;
    sint_t mouse_x;
    sint_t mouse_y;
};

void
rr_input_destroy(rr_input_t rr_input)
{
    free(rr_input);
}

rr_input_t
rr_input_create(void)
{
    rr_input_t rr_input;
    rr_input = malloc(sizeof(*rr_input));
    if (rr_input == NULL) {
        return NULL;
    }

    rr_input->is_quit = 0;
    rr_input->key_states = calloc(sizeof(*rr_input->key_states), RR_INPUT_NUM_KEYS);
    rr_input->prev_key_states = calloc(sizeof(*rr_input->prev_key_states), RR_INPUT_NUM_KEYS);
    rr_input->mouse_state = 0;
    rr_input->mouse_x = 0;
    rr_input->mouse_y = 0;

    return rr_input;
}

void
rr_input_fetch_state(rr_input_t rr_input)
{
    SDL_Event event;
    memcpy(rr_input->prev_key_states, rr_input->key_states, RR_INPUT_NUM_KEYS);
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT: 
                rr_input->is_quit = 1; /* TODO: make it a game event */
                break;
            case SDL_KEYDOWN: 
                rr_input->key_states[event.key.keysym.scancode] = 1;
                break;
            case SDL_KEYUP: 
                rr_input->key_states[event.key.keysym.scancode] = 0;
                //rr_input->key_states = SDL_GetKeyboardState(&rr_input->num_keys); 
                break;
            case SDL_MOUSEMOTION:
            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP: 
                rr_input->mouse_state = SDL_GetMouseState(&rr_input->mouse_x, &rr_input->mouse_y); 
                break;
        }
    }
}

rr_input_is_key_down(rr_input_t rr_input, int key_code)
{
    return rr_input->key_states[key_code];
}

rr_input_is_key_up(rr_input_t rr_input, int key_code)
{
    return !rr_input->key_states[key_code];
}

int
rr_input_is_key_pressed(rr_input_t rr_input, int key_code)
{
    return rr_input->key_states[key_code] && !rr_input->prev_key_states[key_code];
}

int
rr_input_is_key_released(rr_input_t rr_input, int key_code)
{
    return !rr_input->key_states[key_code] && rr_input->prev_key_states[key_code];
}

int
rr_input_is_mouse_button_pressed(rr_input_t rr_input, int mouse_button)
{
    return rr_input->mouse_state & SDL_BUTTON(mouse_button);
}

void
rr_input_get_mouse_position(rr_input_t rr_input, int *x, int *y)
{
    if (x) {
        *x = rr_input->mouse_x;
    }

    if (y) {
        *y = rr_input->mouse_y;
    }
}

/* TODO: remove once a game event */
int
rr_input_is_quit(rr_input_t rr_input)
{
    return rr_input->is_quit;
}

/* TODO: REMOVE */
float_t
rr_input_get_mouse_x(rr_input_t rr_input)
{
    return rr_input->mouse_x;
}

/* TODO: REMOVE */
float_t
rr_input_get_mouse_y(rr_input_t rr_input)
{
    return rr_input->mouse_y;
}

/* TODO: REMOVE */
byte_t
rr_input_get_key_state(rr_input_t rr_input, int key_code)
{
    return rr_input->key_states ? rr_input->key_states[key_code] : NULL;
}