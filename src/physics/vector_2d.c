#include "physics/vector_2d.h"
#include "types/types_basic.h"

/* TODO: consider macros */

inline vector_2d_t
vector_2d_add(vector_2d_t v1, vector_2d_t v2)
{
    vector_2d_t v3 = {v1.x + v2.x, v1.y + v2.y};
    return v3;
}

inline vector_2d_t
vector_2d_sub(vector_2d_t v1, vector_2d_t v2)
{
    vector_2d_t v3 = {v1.x - v2.x, v1.y - v2.y};
    return v3;
}

/* TODO: is this needed? */
inline vector_2d_t
vector_2d_mult(vector_2d_t v, vector_2d_t v2)
{
    vector_2d_t v3 = {v.x * v2.x, v.y * v2.y};
    return v3;
}

inline vector_2d_t
vector_2d_div(vector_2d_t v, vector_2d_t v2)
{
    float_t x = !v2.x ? 0.000000001f : v2.x; /* TODO: is this wise??? */
    float_t y = !v2.y ? 0.000000001f : v2.y; /* TODO: is this wise??? */

    vector_2d_t v3 = {v.x / x, v.y / y};
    return v3;
}

inline vector_2d_t
vector_2d_scalar_mult(vector_2d_t v, float_t scalar)
{
    vector_2d_t v2 = {v.x * scalar, v.y * scalar};
    return v2;
}

inline vector_2d_t
vector_2d_scalar_div(vector_2d_t v, float_t scalar)
{
    float_t s = !scalar ? 0.000000001f : scalar; /* TODO: is this wise??? */
    vector_2d_t v2 = {v.x / s, v.y / s};
    return v2;
}

inline float_t
vector_2d_dot(vector_2d_t v, vector_2d_t v2)
{
    return (v.x * v2.x) + (v.y * v2.y); /* TODO: overflow */
}

/*
inline vector_2d_t
vector_2d_cross(vector_2d_t v, vector_2d_t v2)
{
}
*/

inline void
vector_2d_print(vector_2d_t v)
{
    printf("vector (%f, %f)\n", v.x, v.y);
}