#ifndef RR_VECTOR_2D_H
#define RR_VECTOR_2D_H

#include <stdio.h>
#include "types/types_basic.h"

// TODO: union to create synonyms (x, y), (w, h)
typedef struct vector_2d_t {
    float_t x;
    float_t y;
} vector_2d_t;

vector_2d_t
vector_2d_add(vector_2d_t v1, vector_2d_t v2);

vector_2d_t
vector_2d_sub(vector_2d_t v1, vector_2d_t v2);

vector_2d_t
vector_2d_mult(vector_2d_t v, vector_2d_t v2);

vector_2d_t
vector_2d_div(vector_2d_t v, vector_2d_t v2);

vector_2d_t
vector_2d_scalar_mult(vector_2d_t v, float_t scalar);

vector_2d_t
vector_2d_scalar_div(vector_2d_t v, float_t scalar);

float_t
vector_2d_dot(vector_2d_t v, vector_2d_t v2);

void
vector_2d_print(vector_2d_t v);

#endif