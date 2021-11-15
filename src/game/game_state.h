#ifndef RR_GAME_STATE_H
#define RR_GAME_STATE_H

#ifdef DO_NOT_COMPILE
#ifndef RR_GAME_SECTION_H
#define RR_GAME_SECTION_H

// TODO: resource locations
/*
#define BMP1_PATHNAME "/home/rricklic/git/c/sdl/graphics/graphics_resources/img1.bmp"
#define SCOTT_PATHNAME "/home/rricklic/git/c/sdl/graphics/graphics_resources/scottpilgrim.png"
#define GUY_PATHNAME "/home/rricklic/git/c/sdl/graphics/graphics_resources/guy.png"
#define SONIC_PATHNAME "/home/rricklic/git/c/sdl/graphics/graphics_resources/sonic.png"
#define BACKGROUND_PATHNAME "/home/rricklic/git/c/sdl/graphics/graphics_resources/background.png"
*/

// TODO: stuff to be in game_section
/*
    if (!(game_engine->character = character_create())) {
        printf("Unable to allocate character\n");
        goto error;
    }

    if (!(game_engine->camera = camera_create(
            (vector_2d_t){0, 0}, 
            (size_2d_t){SCREEN_WIDTH, SCREEN_HEIGHT}, 
            (vector_2d_t){-1920, -1080}, 
            (vector_2d_t){1920, 1080}, 
            (size_2d_t){78, 82}))) { // TODO: image/level size 
        printf("Unable to allocate camera\n");
        goto error;
    }

    texture_manager_add(game_engine->texture_manager, game_engine->renderer, "guy", GUY_PATHNAME);
    texture_manager_add(game_engine->texture_manager, game_engine->renderer, "sonic", SONIC_PATHNAME);
    texture_manager_add(game_engine->texture_manager, game_engine->renderer, "background", BACKGROUND_PATHNAME);
*/

// TODO: update characters/object/screen/camera based on input
/*
    character_handle_input(game_engine->character, game_engine->input);

    if (game_engine->input->key_states) {
        if (game_engine->input->key_states[SDL_SCANCODE_Z]) {
            camera_set_zoom(game_engine->camera, 2, 1); //ZOOM IN
        } else if (game_engine->input->key_states[SDL_SCANCODE_C]) {
            camera_set_zoom(game_engine->camera, 1, 1);
        } else if (game_engine->input->key_states[SDL_SCANCODE_X]) {
            camera_set_zoom(game_engine->camera, 0.25, 1); // ZOOM OUT
        } else if (game_engine->input->key_states[SDL_SCANCODE_R]) {
            camera_set_shake(game_engine->camera, 0.25, 10);
        }
    }
*/


#define T game_section_t
typedef struct T *T;

void
game_section_destroy(T game_section);

T
game_section_create();

#undef T

#endif
#endif

/*
#include "game_section.h"

#define T game_section_t
struct T {
    
};

void
game_section_destroy(T *game_section)
{
    free(game_section);
}

T *
game_section_create()
{
    T *game_section = NULL;

    game_section = (T *)malloc(sizeof(T);
    if (!game_section) {
        printf("Unable to allocate game_section\n");
        return NULL;
    }

    // TODO:

    return game_section;
}

#undef T

#endif
*/

#endif