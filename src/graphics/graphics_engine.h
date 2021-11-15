#ifndef RR_GRAPHICS_ENGINE_H
#define RR_GRAPHICS_ENGINE_H

#include "graphics/texture_manager.h"
#include "graphics/renderer.h"
#include "graphics/window.h"

typedef struct graphics_engine_t {
    window_t *window;
    renderer_t *renderer;
    texture_manager_t *texture_manager;
} graphics_engine_t;

graphics_engine_t *
graphics_engine_create(int screen_width, int screen_height);

void
graphics_engine_destroy(graphics_engine_t * graphics_engine);

#define graphics_get_window_size(g, w, h) SDL_GetWindowSize(g->window, w, h);

#endif
