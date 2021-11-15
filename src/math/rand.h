#ifndef RR_RAND_H
#define RR_RAND_H

#include <stdlib.h>

#define RR_MAX_RAND RAND_MAX 

#include "types/types_basic.h"

static inline float_t
rr_rand_seed(uint_t seed)
{
    srand(seed);
}

static inline float_t
rr_rand_0_to_1(void)
{
    return rand() / (float_t)RR_MAX_RAND;
}

static inline float_t
rr_rand_mod(uint_t mod)
{
    return rand() % mod;
}

static inline float_t
rr_rand_neg1_to_pos1(void)
{
    return 1 - (2.f * rand() / (float_t)RR_MAX_RAND);
}

#ifdef DO_NOT_COMPILE
#include <stdint.h>

uint32_t state;


inline uint32_t
rand_xor_shift_1(void)
{
    state ^= (state << 13);
    state ^= (state >> 17);
    state ^= (state << 5);
    return state;
}

inline uint32_t
rand_xor_shift_128(void)
{

}

inline uint32_t
rand_xor_shift_64_star(void)
{

}

inline uint32_t
rand_mersenne_twister(void)
{

}

/**
 * Lehmer / Park-Miller
 * 1. Scale by prime S
 * 2. Modulo by prime M
 * NOTE: do not seed with zero
 */ 
inline uint32_t
rand_lehmer_park_miller(void)
{
    state = (state * 0x0000BC8F) % 0x7FFFFFFF;
    return state;
}

/**
 * Mixed Congruential Generators (MCG)
 * 1. Scale by S
 * 2. Add bias B
 * 3. Modulo by M
 */
inline uint32_t
rand_mcg(void)
{
    state = ((state * 0x0019660D) + 0x3C6EF35F) & 0x7FFFFFFF;
    return state;
}
#endif 

#endif    