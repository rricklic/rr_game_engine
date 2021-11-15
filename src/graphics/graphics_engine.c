#include <SDL.h> /* Core SDL functionality */
#include <SDL_image.h> /* JPG/PNG image loading */
#include <SDL_ttf.h> /* True Type Font (TTF) loading */

#include "graphics/graphics_engine.h"

/*
SDL_WINDOW_FULLSCREEN //fullscreen window
SDL_WINDOW_FULLSCREEN_DESKTOP //fullscreen window at the current desktop resolution
SDL_WINDOW_OPENGL //window usable with OpenGL context
SDL_WINDOW_VULKAN //window usable with a Vulkan instance
SDL_WINDOW_HIDDEN //window is not visible
SDL_WINDOW_BORDERLESS //no window decoration
SDL_WINDOW_RESIZABLE //window can be resized
SDL_WINDOW_MINIMIZED //window is minimized
SDL_WINDOW_MAXIMIZED //window is maximized
SDL_WINDOW_INPUT_GRABBED //window has grabbed input focus
SDL_WINDOW_ALLOW_HIGHDPI //window should be created in high-DPI mode if supported (>= SDL 2.0.1)
*/

static int
graphics_engine_start()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL_Init failed: %s\n", SDL_GetError());
        return 1;
    }

    if (!(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) & (IMG_INIT_JPG | IMG_INIT_PNG))) {
        printf("IMG_Init did not init correctly %s\n", IMG_GetError());
        return 1;
    }

    if (TTF_Init() == -1) {
        printf("TTF_Init did not init correctly %s\n", TTF_GetError());
        return 1;
    }

    return 0;
}

static void
graphics_engine_stop()
{
    TTF_Quit();
    IMG_Quit();
    SDL_Quit(); 
}

graphics_engine_t *
graphics_engine_create(int screen_width, int screen_height)
{
    graphics_engine_t *graphics_engine;

    if (graphics_engine_start()) {
        return NULL;
    }

    graphics_engine = (graphics_engine_t *)malloc(sizeof(graphics_engine_t));
    if (!graphics_engine) {
        return NULL;
    }

    graphics_engine->window = window_create("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screen_width, screen_height, SDL_WINDOW_OPENGL /*| SDL_WINDOW_FULLSCREEN*/);
    if (!graphics_engine->window) {
        printf("SDL_CreateWindow failed: %s\n", SDL_GetError());
        graphics_engine_destroy(graphics_engine);
        return NULL;
    }

    graphics_engine->renderer = renderer_create(graphics_engine->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!graphics_engine->renderer) {
        printf("SDL_CreateRenderer failed: %s\n", SDL_GetError());
        graphics_engine_destroy(graphics_engine);
        return NULL;
    }
    /* TODO: make parameter */
    /* Enable alpha blending (e.g.: transparency) */
    if (SDL_SetRenderDrawBlendMode(graphics_engine->renderer, SDL_BLENDMODE_BLEND) != 0) {
        printf("SDL_SetRenderDrawBlendMode failed: %s\n", SDL_GetError());
    }

    graphics_engine->texture_manager = texture_manager_create();
    if (!graphics_engine->texture_manager) {
        printf("Unable to allocate texture_manager\n");
        graphics_engine_destroy(graphics_engine);
        return NULL;
    }

    return graphics_engine;
}

void
graphics_engine_destroy(graphics_engine_t *graphics_engine)
{
    free(graphics_engine);
    graphics_engine_stop();
}
