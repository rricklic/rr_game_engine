#ifndef RR_PARTICLE_SYSTEM_H
#define RR_PARTICLE_SYSTEM_H

#include "math/vector.h"
#include "types/types_basic.h"
#include "graphics/graphics_engine.h"

/**
 * lifetime: 
 *     amount of time
 *     within position
 *     contact
 *     visible
 */
typedef struct particle_t {
    vector_2df_t position;
    vector_2df_t velocity;
    float_t rotation;
    float_t rotation_velocity;
    float_t size_start;
    float_t lifetime_left;
    int is_active;
} particle_t;

typedef struct particle_props_t {
    vector_2df_t velocity;
    vector_2df_t velocity_variation;
    float_t rotation;
    float_t rotation_velocity;
    float_t size_start;
    float_t size_end;
    float_t size_variation;
    byte_t color_start[4];
    byte_t color_end[4];
    float_t lifetime;
} particle_props_t;

typedef struct particle_system_t {
    particle_props_t particle_props;
    particle_t *particles;
    uint_t particle_count;
    uint_t particle_index;
} particle_system_t;

particle_system_t *
particle_system_create(uint_t particles_count, particle_props_t particle_props);

void
particle_system_destroy(particle_system_t *particle_system);

void
particle_system_emit(particle_system_t *particle_system, vector_2df_t position);

void
particle_system_update(particle_system_t *particle_system, float_t dt);

void
particle_system_render(particle_system_t *particle_system, renderer_t *rr_renderer);

#endif