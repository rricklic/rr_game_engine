#include <stdlib.h>

#include "rr_sprite.h"

rr_sprite_t *
rr_sprite_create(uint_t width, uint_t height, uint_t origin_x, uint_t origin_y, texture_t *texture)
{
    rr_sprite_t *rr_sprite;
    rr_sprite = malloc(sizeof(*rr_sprite));
    if (rr_sprite == NULL) {
        return NULL;
    }

    rr_sprite->texture = NULL; /* TODO: */

    rr_sprite->width = width;
    rr_sprite->height = height;
    rr_sprite->origin_x = origin_x;
    rr_sprite->origin_y = origin_y;

    return rr_sprite;
}

void
rr_sprite_destroy(rr_sprite_t *rr_sprite)
{
    if (rr_sprite) {
        free(rr_sprite->texture);
        free(rr_sprite);
    }
}