#ifndef RR_COLLISION_MANAGER_H
#define RR_COLLISION_MANAGER_H

// USE GJK distance algorithm

// Conservative advancement with iteration => bilateral advancement

// root finding problem - algorithms to find solutions
// numerical root finding

// !!!!!!!!!!!!!!!!!!!!!!!
// interpolate motion/rotation between 2 frames (t=0, t=1)
// evaluate separation function (s(t) = n*p(t) - w)
// braket root: if signs of s(0) amd s(1) are different, theres a root! (where is a (0 >= t >= 1) where s(t) = 0)
// bisection/false position/both to solve for root
//
// MULTIPLE ROOTS POSSIBLE WITH ROTATION (NOT POSSIBLE WITH ONLY TRANSLATION)

// 1. broad phase - could objects collide
// 2. narrow phase - did objects collide
// 3. resolution - update objects


#include "object/rr_object.h";

void
rr_collision_register_object(rr_object_t rr_object);

void
rr_collision_subscribe(unsigned int target_resource_id, unsigned int colliding_resource_id, void(*func)(unsigned int colliding_resource_id, void *data));

void
rr_collision_handle();

#endif
