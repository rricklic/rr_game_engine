#ifndef RR_IMAGE_H
#define RR_IMAGE_H

#include <SDL_image.h> /* JPG/PNG image loading */

#define image_get_error() IMG_GetError()
#define image_load(i) IMG_Load(i)

#endif