//#include <stdio.h>

#include "particle/particle_system.h"

#include "math/lerp.h"
#include "math/rand.h"
#include "graphics/primitives.h"
#include "graphics/renderer.h"

/**
 * 
 *  https://www.youtube.com/watch?v=GK0jHlv3e3w
 *  11:00 
 * 
 */ 

particle_system_t *
particle_system_create(uint_t particle_count, particle_props_t particle_props)
{
    particle_system_t *particle_system;
    particle_system = malloc(sizeof(particle_system_t));
    if (!particle_system) {
        return NULL;
    }

    particle_system->particles = calloc(sizeof(particle_t), particle_count);
    if (!particle_system->particles) {
        free(particle_system);
        return NULL;
    }

    particle_system->particle_props = particle_props;
    particle_system->particle_count = particle_count;
    particle_system->particle_index = particle_count - 1;
    return particle_system;
}

void
particle_system_destroy(particle_system_t *particle_system)
{
    if (particle_system) {
        free(particle_system->particles);
        free(particle_system);
    }
}

void
particle_system_emit(particle_system_t *particle_system, vector_2df_t position)
{
    //printf("Emit particle: (%f, %f)\n", particle_props.x, particle_props.y);

    particle_t *particle = &particle_system->particles[particle_system->particle_index];
    particle->is_active = 1;
    particle->position = position;
    particle->velocity.x = particle_system->particle_props.velocity.x + (particle_system->particle_props.velocity_variation.x * (rr_rand_0_to_1() - 0.5f));
    particle->velocity.y = particle_system->particle_props.velocity.y + (particle_system->particle_props.velocity_variation.y * (rr_rand_0_to_1() - 0.5f));
    particle->rotation = rr_rand_0_to_1() * particle_system->particle_props.rotation; //rr_rand_0_to_1() * 2.f * 3.14f; /* TODO: pi */
    particle->rotation_velocity = particle_system->particle_props.rotation_velocity * rr_rand_neg1_to_pos1();
    particle->size_start = particle_system->particle_props.size_start + (particle_system->particle_props.size_variation * (rr_rand_0_to_1() - 0.5f));
    particle->lifetime_left = particle_system->particle_props.lifetime;
    particle_system->particle_index = --particle_system->particle_index % particle_system->particle_count;
}

void
particle_system_update(particle_system_t *particle_system, float_t dt)
{
    for (int i = 0; i < particle_system->particle_count; i++) {
        if (!particle_system->particles[i].is_active) {
            continue;
        }

        if (particle_system->particles[i].lifetime_left <= 0.f) {
            particle_system->particles[i].is_active = 0;
            continue;
        }

        //printf("Update particle: (%f, %f)\n", particle_system->particles[i].x, particle_system->particles[i].y);

        particle_system->particles[i].lifetime_left -= dt;
        if (particle_system->particles[i].lifetime_left < 0.f) {
            particle_system->particles[i].lifetime_left = 0.f;
        }
        particle_system->particles[i].position = vector_2df_add(
            particle_system->particles[i].position, 
            vector_2df_mult(particle_system->particles[i].velocity, dt));
        particle_system->particles[i].rotation += particle_system->particles[i].rotation_velocity * dt;
    }
}

void
particle_system_render(particle_system_t *particle_system, renderer_t *rr_renderer)
{
    float_t particle_size;
    float_t particle_size_half;
    byte_t color[4];
    
    for (int i = particle_system->particle_count - 1; i >= 0; i--) {
        if (!particle_system->particles[i].is_active) {
            continue;
        }

        /* NOTE: start/end intentionally reversed */

        float life_left = particle_system->particles[i].lifetime_left / particle_system->particle_props.lifetime;
        particle_size = lerp_1d(particle_system->particle_props.size_end, particle_system->particles[i].size_start, life_left); /* intentionally reversed */
        particle_size_half = particle_size / 2.f;
        
        color[0] = lerp_1d(particle_system->particle_props.color_end[0], particle_system->particle_props.color_start[0], lerp_smooth_start_2(life_left)); 
        color[1] = lerp_1d(particle_system->particle_props.color_end[1], particle_system->particle_props.color_start[1], lerp_smooth_start_2(life_left));
        color[2] = lerp_1d(particle_system->particle_props.color_end[2], particle_system->particle_props.color_start[2], lerp_smooth_start_2(life_left));
        color[3] = lerp_1d(particle_system->particle_props.color_end[3], particle_system->particle_props.color_start[3], lerp_smooth_start_2(life_left));

        render_rotate(particle_system->particles[i].position.x, particle_system->particles[i].position.y, particle_system->particles[i].rotation);
        
        //printf("Render particle: (%f, %f)\n", particle->x, particle->y);
        primatives_fill_rect(
            rr_renderer,
            particle_system->particles[i].position.x-particle_size_half,
            particle_system->particles[i].position.y-particle_size_half,
            particle_size,
            particle_size,
            0,
            0,
            color);
    }

    render_rotate_reset();
}