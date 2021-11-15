#ifndef RR_INPUT_H
#define RR_INPUT_H

#include <SDL_scancode.h>

#include "types/types_basic.h"

/* Keyboard codes */
#define RR_KEYBOARD_A SDL_SCANCODE_A
#define RR_KEYBOARD_B SDL_SCANCODE_B
#define RR_KEYBOARD_C SDL_SCANCODE_C
#define RR_KEYBOARD_D SDL_SCANCODE_D
#define RR_KEYBOARD_E SDL_SCANCODE_E
#define RR_KEYBOARD_F SDL_SCANCODE_F
#define RR_KEYBOARD_G SDL_SCANCODE_G
#define RR_KEYBOARD_H SDL_SCANCODE_H
#define RR_KEYBOARD_I SDL_SCANCODE_I
#define RR_KEYBOARD_J SDL_SCANCODE_J
#define RR_KEYBOARD_K SDL_SCANCODE_K
#define RR_KEYBOARD_L SDL_SCANCODE_L
#define RR_KEYBOARD_M SDL_SCANCODE_M
#define RR_KEYBOARD_N SDL_SCANCODE_N
#define RR_KEYBOARD_O SDL_SCANCODE_O
#define RR_KEYBOARD_P SDL_SCANCODE_P
#define RR_KEYBOARD_Q SDL_SCANCODE_Q
#define RR_KEYBOARD_R SDL_SCANCODE_R
#define RR_KEYBOARD_S SDL_SCANCODE_S
#define RR_KEYBOARD_T SDL_SCANCODE_T
#define RR_KEYBOARD_U SDL_SCANCODE_U
#define RR_KEYBOARD_V SDL_SCANCODE_V
#define RR_KEYBOARD_W SDL_SCANCODE_W
#define RR_KEYBOARD_X SDL_SCANCODE_X
#define RR_KEYBOARD_Y SDL_SCANCODE_Y
#define RR_KEYBOARD_Z SDL_SCANCODE_Z
#define RR_KEYBOARD_0 SDL_SCANCODE_0
#define RR_KEYBOARD_1 SDL_SCANCODE_1
#define RR_KEYBOARD_2 SDL_SCANCODE_2
#define RR_KEYBOARD_3 SDL_SCANCODE_3
#define RR_KEYBOARD_4 SDL_SCANCODE_4
#define RR_KEYBOARD_5 SDL_SCANCODE_5
#define RR_KEYBOARD_6 SDL_SCANCODE_6
#define RR_KEYBOARD_7 SDL_SCANCODE_7
#define RR_KEYBOARD_8 SDL_SCANCODE_8
#define RR_KEYBOARD_9 SDL_SCANCODE_9
#define RR_KEYBOARD_UP SDL_SCANCODE_UP
#define RR_KEYBOARD_DOWN SDL_SCANCODE_DOWN
#define RR_KEYBOARD_LEFT SDL_SCANCODE_LEFT
#define RR_KEYBOARD_RIGHT SDL_SCANCODE_RIGHT
#define RR_KEYBOARD_SPACE SDL_SCANCODE_SPACE
#define RR_KEYBOARD_ENTER SDL_SCANCODE_KP_ENTER
#define RR_KEYBOARD_TAB SDL_SCANCODE_TAB
#define RR_KEYBOARD_L_SHIFT SDL_SCANCODE_L_SHIFT
#define RR_KEYBOARD_R_SHIFT SDL_SCANCODE_R_SHIFT
#define RR_KEYBOARD_L_CTRL SDL_SCANCODE_L_CTRL
#define RR_KEYBOARD_R_CTRL SDL_SCANCODE_R_CTRL
#define RR_KEYBOARD_L_ALT SDL_SCANCODE_L_ALT
#define RR_KEYBOARD_R_ALT SDL_SCANCODE_R_ALT

/* Mouse codes */
/* TODO: distinquish between left/right button presses/releases */
#define RR_MOUSE_MOTION SDL_MOUSEMOTION
#define RR_MOUSE_BUTTON_L_DOWN SDL_MOUSEBUTTONDOWN
#define RR_MOUSE_BUTTON_L_UP SDL_MOUSEBUTTONUP
#define RR_MOUSE_BUTTON_R_DOWN SDL_MOUSEBUTTONDOWN
#define RR_MOUSE_BUTTON_R_UP SDL_MOUSEBUTTONUP
#define RR_MOUSE_SCROLL SDL_MOUSESCROLL

typedef struct rr_input_t *rr_input_t;

void
rr_input_destroy(rr_input_t rr_input);

rr_input_t
rr_input_create(void);

void
rr_input_fetch_state(rr_input_t rr_input);

int
rr_input_is_key_down(rr_input_t rr_input, int key_code);

int
rr_input_is_key_up(rr_input_t rr_input, int key_code);

int
rr_input_is_key_pressed(rr_input_t rr_input, int key_code);

int
rr_input_is_key_released(rr_input_t rr_input, int key_code);

int
rr_input_is_quit(rr_input_t rr_input);

/* TODO: REMOVE */
float_t
rr_input_get_mouse_x(rr_input_t rr_input);

/* TODO: REMOVE */
float_t
rr_input_get_mouse_y(rr_input_t rr_input);

/* TODO: REMOVE */
byte_t
rr_input_get_key_state(rr_input_t rr_input, int key_code);

#endif