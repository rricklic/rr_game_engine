
#include <SDL_ttf.h> /* True Type Font (TTF) loading */

#include "types/rect.h"
#include "rr_texture.h"
#include "text_renderer.h"

void
text_renderer_text(renderer_t *renderer, const char *string, int x, int y, int screen_width, int screen_height)
{
    TTF_Font *font = NULL;
    surface_t *surface = NULL;
    texture_t *texture = NULL;

    font = TTF_OpenFont("/usr/share/fonts/truetype/freefont/FreeMono.ttf", 28); // TODO:
    if (!font) {
        printf("TTF_OpenFont failed: %s\n", TTF_GetError());
        return;
    }

    surface = TTF_RenderText_Solid(font, string, (SDL_Color){0xFF, 0xFF, 0xFF});
    if (!surface) {
        printf("TTF_RenderText_Solid failed: %s\n", TTF_GetError());
        TTF_CloseFont(font);
        return;
    }

    texture = render_create_texture_from_surface(renderer, surface);
    if (!texture) {
        printf("render_create_texture_from_surface failed: %s\n", "???");
        surface_free(surface);
        TTF_CloseFont(font);
        return;
    }

    int w, h;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);

    rect_t src_rect = {0, 0, screen_width, screen_height};
    rect_t dst_rect = {x, y, w, h};

    render_copy(renderer, texture, &src_rect, &dst_rect);

    texture_destroy(texture);
    surface_free(surface);
    TTF_CloseFont(font);
}