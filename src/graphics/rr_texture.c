#include "graphics/rr_texture.h"
#include "graphics/renderer.h"
#include "types/types_basic.h"

texture_t *
rr_texture_create(char *filename, byte_t transparent_rgb[3])
{
    return NULL;

#ifdef DO_NOT_COMPILE
    surface_t *surface;
    texture_t *texture;

    surface = image_load(filename);
    if (surface == NULL) {
        return NULL;
    }

    /*Set transparent pixel color*/
    if (transparent_rgb) {
        if (SDL_SetColorKey(surface, SDL_TRUE, 
                SDL_MapRGB(surface->format, transparent_rgb[0], transparent_rgb[1], transparent_rgb[2])) < 0) {
            surface_free(surface);
            return NULL;
        }
    }

    texture = render_create_texture_from_surface(renderer, surface);
    if (texture == NULL) {
        printf("render_create_texture_from_surface failed: %s\n", get_error());
        surface_free(surface);
        return;
    }

    surface_free(surface);

    return texture;
#endif
}