#ifndef RR_LERP_H
#define RR_LERP_H

#include "physics/vector_2d.h"

/*
https://github.com/warrenm/AHEasing/blob/377c12940c14fb9e0a4959060a388b498b2056e5/AHEasing/easing.c
*/

float
lerp_range_map(float in, float in_start, float in_end, float out_start, float out_end, float(*lerp_func)(float t));

/*
 TODO: time to take to move from start to end
 TODO: delay before starting
*/

/**
 * percent [0, 1]
 */
float
lerp_1d(float start, float end, float percent);

vector_2d_t
lerp_2d(vector_2d_t start, vector_2d_t end, float percent);

float
lerp_linear(float t);

float
lerp_linear_bounce(float t);

float
lerp_smooth_start_2(float t);

float
lerp_smooth_start_3(float t);

float
lerp_smooth_start_4(float t);

float
lerp_smooth_stop_2(float t);

float
lerp_smooth_stop_3(float t);

float
lerp_smooth_stop_4(float t);

float
lerp_smooth_step_2(float t);

float
lerp_smooth_step_3(float t);

float
lerp_smooth_step_4(float t);

float
lerp_smooth_arch_2(float t);

float
lerp_smooth_mix(float (*func1)(float), float (*func2)(float), float weight, float t);

float
lerp_smooth_crossfade(float (*func1)(float), float (*func2)(float), float t);

float
lerp_scale(float (*func)(float), float t);

float
lerp_reverse_scale(float (*func)(float), float t);

float
lerp_arch_2(float t);

float
lerp_reverse_arch_2(float t);

float
lerp_smooth_start_arch_3(float t);

float
lerp_smooth_stop_arch_3(float t);

float
lerp_bell_curve_6(float t);

/*
float
lerp_bounce_bottom(float t);

float
lerp_bounce_top(float t);

float
lerp_bounce_bottom_top(float t);
*/

float
lerp_bounce_ease_out(float t);

float
lerp_bounce_reverse_ease_out(float t);

float
lerp_bounce_ease_in(float t);

float
lerp_bounce_reverse_ease_in(float t);

float
lerp_bounce_ease_in_out(float t);

#endif