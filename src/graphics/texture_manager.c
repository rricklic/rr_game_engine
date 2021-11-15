#include "graphics/texture_manager.h"
#include "graphics/rr_texture.h"
#include "graphics/image.h"
#include "graphics/renderer.h"
#include "core/error.h"
#include "types/map.h"
#include "types/rect.h"
#include "types/types_basic.h"

typedef struct texture_manager_impl_t {
    map_void_t *texture_map;
} texture_manager_impl_t;

static inline void
texture_manager_impl_free(texture_manager_impl_t *impl)
{
    const char *id;
    texture_t *texture;
    map_iter_t iter;

    if (impl) {
        if (impl->texture_map) {
            iter = map_iter(impl->texture_map);
            
            while((id = map_next(impl->texture_map, &iter))) {
                texture = *(texture_t **)map_get(impl->texture_map, id);
                texture_destroy(texture);
            }

            map_deinit(impl->texture_map);
            free(impl->texture_map);
        }
        
        free(impl);
    }
}

void
texture_manager_free(texture_manager_t *texture_manager)
{
    if (texture_manager) {
        texture_manager_impl_free(texture_manager->impl);
        free(texture_manager);
    }
}

texture_manager_t *
texture_manager_create(void)
{
    texture_manager_t *texture_manager = NULL;
    texture_manager_impl_t *impl = NULL;
    map_void_t *map = NULL;

    if (!(texture_manager = (texture_manager_t *)malloc(sizeof(texture_manager_t)))) {
        goto error;
    }

    if (!(impl = (texture_manager_impl_t *)malloc(sizeof(texture_manager_impl_t)))) {
        goto error;
    }

    if (!(map = (map_void_t *)malloc(sizeof(map_void_t)))) {
        goto error;
    }
    map_init(map);

    impl->texture_map = map;
    texture_manager->impl = impl;
    return texture_manager;

  error:
    free(map);
    free(impl);
    free(texture_manager);
    return NULL;
}

void
texture_manager_remove(texture_manager_t *texture_manager, char *id)
{
    texture_manager_impl_t *impl = (texture_manager_impl_t *)texture_manager->impl;
    texture_t **texture = (texture_t **)map_get(impl->texture_map, id);
    if (texture) {
        texture_destroy(*texture);
        map_remove(impl->texture_map, id);
    }
}

/* TODO: error handling */
void
texture_manager_add(texture_manager_t *texture_manager, renderer_t *renderer, char *id, char *pathname)
{
    surface_t *surface = NULL;
    texture_t *texture = NULL;

    texture_manager_impl_t *impl = (texture_manager_impl_t *)texture_manager->impl;

    if (!(surface = image_load(pathname))) {
        printf("image_load failed for %s: %s\n", pathname, image_get_error());
        return;
    }

/* TODO: */
/*
    if (transparent_rgb && SDL_SetColorKey(surface, SDL_TRUE,
            SDL_MapRGB(surface->format, transparent_rgb[0], transparent_rgb[1], transparent_rgb[2])) < 0) {
        printf("SDL_SetColorKey (transparency color) failed: %s\n", get_error());
        goto error;
    }
*/

    if (!(texture = render_create_texture_from_surface(renderer, surface))) {
        printf("render_create_texture_from_surface failed: %s\n", get_error());
        surface_free(surface);
        return;
    }
    surface_free(surface);

    texture_manager_remove(texture_manager, id);
    map_set(impl->texture_map, id, texture);
}

/*
texture_t *
create_texture(
        char *pathname,
        renderer_t *renderer,
        uint32_t *transparent_rgb)
{
    surface_t *surface = NULL;
    texture_t *texture = NULL;

    if (!(surface = image_load(pathname))) {
        printf("image_load failed for %s: %s\n", pathname, image_get_error());
        goto error;
    }

    if (transparent_rgb && SDL_SetColorKey(surface, SDL_TRUE,
            SDL_MapRGB(surface->format, transparent_rgb[0], transparent_rgb[1], transparent_rgb[2])) < 0) {
        printf("SDL_SetColorKey (transparency color) failed: %s\n", get_error());
        goto error;
    }

    if (!(texture = render_create_texture_from_surface(renderer, surface))) {
        printf("render_create_texture_from_surface failed: %s\n", get_error());
        goto error;
    }

  error:
    surface_free(surface);
    return texture;
}

texture_t *
create_text_texture(
        char *pathname,
        char *text,
        int point_size,
        renderer_t *renderer,
        uint32_t *rgb)
{
    TTF_Font *font = NULL;
    surface_t *surface = NULL;
    texture_t *texture = NULL;
    SDL_Color text_color = {0x00, 0x00, 0x00};
    if (rgb) {
        text_color.r = rgb[0];
        text_color.g = rgb[1];
        text_color.b = rgb[2];
    }

    if (!(font = TTF_OpenFont(pathname, point_size))) {
        printf("TTF_OpenFont failed: %s\n", TTF_GetError());
        goto error;
    }

    if (!(surface = TTF_RenderText_Solid(font, text, text_color))) {
        printf("TTF_RenderText_Solid failed: %s\n", TTF_GetError());
        goto error;
    }

    if (!(texture = render_create_texture_from_surface(renderer, surface))) {
        printf("render_create_texture_from_surface failed: %s\n", get_error());
        goto error;
    }

  error:
    surface_free(surface);
    TTF_CloseFont(font); // Opening/closing font likely not efficient...
    return texture;
}
*/

void
texture_manager_render(
    texture_manager_t *texture_manager, 
    renderer_t *renderer, 
    char *id, 
    sint_t x,
    sint_t y,
    uint_t w,
    uint_t h,
    sint_t camera_x,
    sint_t camera_y)
{
    texture_t *texture = NULL;
    texture_manager_impl_t *impl = (texture_manager_impl_t *)texture_manager->impl;
    texture = *(texture_t **)map_get(impl->texture_map, id);
    rect_t src_rect = {0, 0, w, h};
    rect_t dst_rect = {x - camera_x, y - camera_y, w, h};

    //SDL_SetTextureColorMod(texture, r, g, b); /* colorize texture*/
    //SDL_SetTextureAlphaMod(texture, a); /* transparency texture*/

   /* render texture into viewport */
   /*
        SDL_Rect viewport;
        viewport.x = 0;
        viewport.y = 0;
        viewport.w = SCREEN_WIDTH / 1.25;
        viewport.h = SCREEN_HEIGHT / 1.25;
        SDL_RenderSetViewport(renderer, &viewport);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
    */

        /* draw primative - eg collision boxes/areas */
/*
        SDL_Rect rect = {SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
        SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
        SDL_RenderFillRect(renderer, &rect);

        SDL_Rect outline_rect = {SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6, SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT * 2 / 3};
        SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
        SDL_RenderDrawRect(renderer, &outline_rect);

        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
        SDL_RenderDrawLine(renderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2);

        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0x00, 0xFF);
        for (int i = 0; i < SCREEN_HEIGHT; i += 4) {
            SDL_RenderDrawPoint(renderer, SCREEN_WIDTH / 2, i);
        }
*/

    render_copy(renderer, texture, &src_rect, &dst_rect);
}

void
texture_manager_render_ex(
    texture_manager_t *texture_manager,
    renderer_t *renderer,
    char *id,
    float_t x,
    float_t y,
    uint_t w,
    uint_t h,
    float_t rotation,
    renderer_flip_t flip_mode)
{
    texture_t *texture = NULL;
    texture_manager_impl_t *impl = (texture_manager_impl_t *)texture_manager->impl;
    texture = *(texture_t **)map_get(impl->texture_map, id);
    rect_t src_rect = {0, 0, w, h};
    rect_t dst_rect = {x, y, w, h};

    render_copy_ex(renderer, texture, &src_rect, &dst_rect, rotation, NULL, flip_mode);
}

void
texture_manager_render_frame(
        texture_manager_t *texture_manager, 
        renderer_t *renderer, 
        char *id, 
        float_t x,
        float_t y,
        uint_t w,
        uint_t h,
        byte_t frame,
        byte_t row)
{
    texture_t *texture = NULL;
    texture_manager_impl_t *impl = (texture_manager_impl_t *)texture_manager->impl;
    texture = *(texture_t **)map_get(impl->texture_map, id);
    rect_t src_rect = {w * frame, h * row, w, h};
    rect_t dst_rect = {x, y, w, h};

    render_copy(renderer, texture, &src_rect, &dst_rect);
}        

void
texture_manager_render_frame_ex(
    texture_manager_t *texture_manager, 
    renderer_t *renderer, 
    char *id, 
    float_t x,
    float_t y,
    uint_t w,
    uint_t h,
    byte_t frame, 
    byte_t row,
    float_t rotation,
    renderer_flip_t flip_mode,
    float_t camera_x,
    float_t camera_y)
{
    texture_t *texture = NULL;
    texture_manager_impl_t *impl = (texture_manager_impl_t *)texture_manager->impl;
    texture = *(texture_t **)map_get(impl->texture_map, id);
    rect_t src_rect = {w * frame, h * row, w, h};
    rect_t dst_rect = {x - camera_x, y - camera_y, w, h};

    render_copy_ex(renderer, texture, &src_rect, &dst_rect, rotation, NULL, flip_mode);
}