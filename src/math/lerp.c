#include <math.h>

#include "math/lerp.h"

/**
 * Also known as tweening, easing, lerping (linear interpolation)
 * 
 * Requires: start point, end point, percentage between points
 */

#define MIX(func1, func2, weight, t) \
    (((1.f - (weight)) * func1(t)) + ((weight) * func2(t)))

/*
#define MIX_2(func1, func2, weight, t) \
    (func1(t) + (weight) * (func2(t) - func1(t)))
*/

#define REVERSE(v) \
    (1 - (v))    

#define CLAMP(a, b, v) \
    ((v) < (a)) ? (a) : ((v) > (b)) ? (b) : (v)

float
lerp_range_map(float in, float in_start, float in_end, float out_start, float out_end, float(*lerp_func)(float t))
{
    float out = in - in_start; /* [0, in_end - in_start] */
    out /= (in_end - in_start); /* [0, 1] */
    if (lerp_func) {
        out = lerp_func(out);
    }
    out *= (out_end - out_start); /* [0, out_end - out_start] */
    return out + out_start; /* [out_start, out_end] */
}

inline float
lerp_1d(float start, float end, float percent)
{
    return start + (end - start) * percent;
}

vector_2d_t
lerp_2d(vector_2d_t start, vector_2d_t end, float percent)
{
    return (vector_2d_t) { 
        .x = (lerp_1d(start.x, end.x, percent)), 
        .y = (lerp_1d(start.y, end.y, percent))
    };
}

inline float
lerp_linear(float t)
{
    return t;
}

inline float
lerp_linear_bounce(float t)
{
    return (t < 0.5f ? t : 1 - t) * 2.f;
}

inline float
lerp_smooth_start_2(float t)
{
    return t * t;
}

inline float
lerp_smooth_start_3(float t)
{
    return t * t * t;
}

inline float
lerp_smooth_start_4(float t)
{
    return t * t * t * t;
}

inline float
lerp_smooth_stop_2(float t)
{
    return 1 - (1 - t) * (1 - t);
}

inline float
lerp_smooth_stop_3(float t)
{
    return 1 - (1 - t) * (1 - t) * (1 - t);
}

inline float
lerp_smooth_stop_4(float t)
{
    return 1 - (1 - t) * (1 - t) * (1 - t) * (1 - t);
}

inline float
lerp_smooth_step_2(float t)
{
    return MIX(lerp_smooth_start_2, lerp_smooth_stop_2, t, t);
}

inline float
lerp_smooth_step_3(float t)
{
    return MIX(lerp_smooth_start_3, lerp_smooth_stop_3, t, t);
}

inline float
lerp_smooth_step_4(float t)
{
    return MIX(lerp_smooth_start_4, lerp_smooth_stop_4, t, t);
}

inline float
lerp_smooth_arch_2(float t)
{
    return (t < 0.5 ? lerp_smooth_start_2(t) : REVERSE(lerp_smooth_stop_2(t))) * 4.f;
}

inline float
lerp_hesitate_2(float t)
{
    return MIX(lerp_smooth_start_2, lerp_smooth_stop_2, 0.5f, t);
}

inline float
lerp_hesitate_3(float t)
{
    return MIX(lerp_smooth_start_3, lerp_smooth_stop_3, 0.5f, t);
}

inline float
lerp_hesitate_4(float t)
{
    return MIX(lerp_smooth_start_4, lerp_smooth_stop_4, 0.5f, t);
}

inline float
lerp_smooth_mix(float (*func1)(float), float (*func2)(float), float weight, float t)
{
    return MIX(func1, func2, weight, t);
}

inline float
lerp_smooth_crossfade(float (*func1)(float), float (*func2)(float), float t)
{
    return MIX(func1, func2, t, t);
}

inline float
lerp_scale(float (*func)(float), float t)
{
    return t * func(t);
}

inline float
lerp_reverse_scale(float (*func)(float), float t)
{
    return (1 - t) * func(t);
}

inline float
lerp_arch_2(float t)
{
    return 4 * t * (1 - t);
}

inline float
lerp_reverse_arch_2(float t)
{
    return 1 - lerp_arch_2(t);
}

inline float
lerp_smooth_start_arch_3(float t)
{
    return t * t * (1 - t); /* lerp_range_map(t * t * (1 - t), 0.f, 0.14f, 0.f, 1.f); */
}

inline float
lerp_smooth_stop_arch_3(float t)
{
    return t * (1 - t) * (1 - t);
}

inline float
lerp_bell_curve_6(float t)
{
    return lerp_smooth_stop_3(t) * lerp_smooth_start_3(t);
}
/*
inline float
lerp_bounce_bottom(float t)
{
    return fabs(t);
}

inline float
lerp_bounce_top(float t)
{
    return 1.f - fabs(1.f - t);
}

inline float
lerp_bounce_bottom_top(float t)
{
    return lerp_bounce_top(lerp_bounce_bottom(t));
}
*/

inline float
lerp_bounce_ease_out(float t)
{
	if (t < 4.f/11.0) {
		return (121.f * t * t)/16.0;
	} else if (t < 8.f/11.0) {
		return (363/40.0 * t * t) - (99/10.0 * t) + 17/5.0;
	} else if (t < 9.f/10.0) {
		return (4356.f/361.0 * t * t) - (35442.f/1805.0 * t) + 16061.f/1805.0;
	} else {
		return (54.f/5.0 * t * t) - (513.f/25.0 * t) + 268.f/25.0;
	}
}

static float
lerp_bounce_ease_out2(float t)
{
	if (t < 4.f/11.0) {
		return (121.f * t * t)/16.0;
	} else if (t < 8.f/11.0) {
		return (363/40.0 * t * t) - (99/10.0 * t) + 17/5.0;
	} else if (t < 9.f/10.0) {
		return (4356.f/361.0 * t * t) - (35442.f/1805.0 * t) + 16061.f/1805.0;
	} else {
		return (54.f/5.0 * t * t) - (513.f/25.0 * t) + 268.f/25.0;
	}
}

inline float
lerp_bounce_reverse_ease_out_old(float t)
{
    return 1.f - lerp_bounce_ease_out(t);
}

inline float
lerp_bounce_reverse_ease_out(float t)
{
    return 1.f - lerp_bounce_ease_out2(t);
}

inline float
lerp_bounce_ease_in(float t)
{
	return 1.f - lerp_bounce_ease_out(1 - t);
}


inline float
lerp_bounce_ease_in_flipped(float t)
{
	return 1.f - lerp_bounce_ease_out(t);
}


inline float
lerp_bounce_reverse_ease_in(float t)
{
	return 1.f - (1.f - lerp_bounce_ease_out(1 - t));
}

inline float
lerp_bounce_ease_in_out(float t)
{
	return t < 0.5 ?
	    0.5 * lerp_bounce_ease_in(t * 2) :
		0.5 * lerp_bounce_ease_out(t * 2 - 1) + 0.5;
}