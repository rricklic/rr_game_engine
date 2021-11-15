#ifndef RR_NOISE_H
#define RR_NOISE_H

#include <stdint.h>

/**
 * Math for Game Programmers: Noise-Based RNG
 * https://www.youtube.com/watch?v=LWFzPP8ZbdU
 * 
 * http://mathforgameprogrammers.com/
 * http://www.essentialmath.com/
 * 
 * fair statistical distribution (99% fair)
 * low degree of repeation (should be statistically correct)
 * high theoretical max repeat period (only to a point)
 * low theoretical max repeat period (CRUICIAL)
 * seedable, with nice range (32-bit), no seeds to avoid
 * fast "warm up"
 * bit independence (spacially/temporally)
 * platform independence (CRUCIAL)
 * order-independence
 * reproducable / deterministic (CRUCIAL)
 * fast - compute, instanciate RNG
 * low memory consumption
 * thread-safe
 */

/**
 * Uses:
 *   Organic procedural generation
 *   Smoothing/easing/tweening functions
 *   Order-independent RNG
 *   Scattering objects in infinite space (use local maxima)
 */

#define NOISE_SQUIRREL_BIT_1 0xB5297A4D
#define NOISE_SQUIRREL_BIT_2 0x68E31DA4
#define NOISE_SQUIRREL_BIT_3 0x1B56C4E9

uint32_t
noise_squirrel_3(uint32_t position, uint32_t seed); // NOTE: position was int...

uint32_t
noise_1d(uint32_t index, uint32_t seed);

uint32_t
noise_2d(uint32_t index_x, uint32_t index_y, uint32_t seed);

float
noise_1d_zero_to_one(uint32_t index, uint32_t seed);

float
noise_2d_zero_to_one(uint32_t index_x, uint32_t index_y, uint32_t seed);

float
noise_1d_neg_one_to_one(uint32_t index, uint32_t seed);

float
noise_2d_neg_one_to_one(uint32_t index_x, uint32_t index_y, uint32_t seed);

#endif    