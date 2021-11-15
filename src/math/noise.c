#include "math/noise.h"


inline uint32_t
noise_squirrel_3(uint32_t position, uint32_t seed) // NOTE: position was int...
{
    position *= NOISE_SQUIRREL_BIT_1;
    position += seed;
    position ^= (position >> 8U);
    position += NOISE_SQUIRREL_BIT_2;
    position ^= (position << 8U);
    position *= NOISE_SQUIRREL_BIT_3;
    position ^= (position >> 8U);
    return (uint32_t)position;
}

inline uint32_t
noise_1d(uint32_t index, uint32_t seed)
{
    return 0; // TODO:
}

inline uint32_t
noise_2d(uint32_t index_x, uint32_t index_y, uint32_t seed)
{
    return 0; // TODO:
}

inline float
noise_1d_zero_to_one(uint32_t index, uint32_t seed)
{
    return 0.f; // TODO:
}

inline float
noise_2d_zero_to_one(uint32_t index_x, uint32_t index_y, uint32_t seed)
{
    return 0.f; // TODO:
}

inline float
noise_1d_neg_one_to_one(uint32_t index, uint32_t seed)
{
    return 0.f; // TODO:
}

inline float
noise_2d_neg_one_to_one(uint32_t index_x, uint32_t index_y, uint32_t seed)
{
    return 0.f; // TODO:
}