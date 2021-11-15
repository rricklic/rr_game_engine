#ifndef RR_VECTOR_H
#define RR_VECTOR_H

#include "types/types_basic.h"

typedef struct vector_2df_t {
    float_t x;
    float_t y;
} vector_2df_t;

typedef struct vector_3df_t {
    float_t x;
    float_t y;
    float_t z;
} vector_3df_t;

typedef struct vector_4df_t {
    float_t x;
    float_t y;
    float_t z;
    float_t a;
} vector_4df_t;

static inline vector_2df_t
vector_2df_add(vector_2df_t v, vector_2df_t w)
{
    return (vector_2df_t){v.x + w.x, v.y + w.y};
}

static inline vector_2df_t
vector_2df_sub(vector_2df_t v, vector_2df_t w)
{
    return (vector_2df_t){v.x - w.x, v.y - w.y};
}

static inline vector_2df_t
vector_2df_mult(vector_2df_t v, float_t c)
{
    return (vector_2df_t){v.x * c, v.y * c};
}

#endif