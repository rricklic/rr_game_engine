#ifndef RR_MATH_H
#define RR_MATH_H

/**
 * Math for Game Programmers: Fast and Funky 1D Nonlinear Transformations
 * GDC
 * https://www.youtube.com/watch?v=mr5xkf6zSzk
 */

/* P(t) = A + t(B - A) - moving from point A to point B where P is position at time t[0, 1] */
/**
 * P(0) = 0 
 * P(1) = 1
 * P(t) != t
 */

#define MIX_1(func1, func2, weight, t) \
    (func1(t) + (weight) * (func2(t) - func1(t)))

#define MIX_2(func1, func2, weight, t) \
    (((1 - (weight)) * func1(t)) + ((weight) * func2(t)))

#define WEIGHTED_AVG() \
    0

/* POW_FAKE(x, 2.2) => ((0.8 * x^2) + (0.2 * x^3)) */
/*
#define POW_FAKE(x, n) \
    (  (x)  )
*/

/*
   damping
   (src * factor + dest * dt) / (factor + dt), where src is the source (starting) value, dest is the destination (target) value, factor is the damping factor (0 = instant, and you can go up from there), and dt is the delta time or frame time.
*/

#endif