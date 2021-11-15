#include <stdlib.h>
#include <time.h> /* time() */

#ifdef DO_NOT_COMPILE

#include <GL/gl.h>

#include "camera.h"

inline float
camera_compute_shake(camera_t camera)
{
    /* shake = [0, 1] */
    float angle = MAX_ANGLE * shake * PERLIN_NOISE(seed, t) /*rand_float(-1, 1)*/;
    float offset_x = MAX_OFFSET * shake * PERLIN_NOISE(seed+1, t) /*rand_float(-1, 1)*/;
    float offset_y = MAX_OFFSET * shake * PERLIN_NOISE(seed+2, t) /*rand_float(-1, 1)*/;

    camera_shaky.angle = camera.angle + angle;
    camera_shaky.center = camera.center + vec_2(offset_x, offset_y);
}

void
camera_free(camera_t *camera)
{
    free(camera);
}

camera_t *
camera_create(
    vector_2d_t position_camera, 
    size_2d_t size_camera, 
    vector_2d_t position_min_camera, 
    vector_2d_t position_max_camera, 
    size_2d_t size_target)
{
    camera_t *camera = NULL;

    if(!(camera = malloc(sizeof(camera_t)))) {
        return NULL;
    }

    camera->position_camera = position_camera;
    camera->position_min_camera = position_min_camera;

    /* TODO: fix... */
    camera->position_max_camera.x = position_max_camera.x - size_camera.width;
    camera->position_max_camera.y = position_max_camera.y - size_camera.height;

    camera->size_camera = size_camera;

    /* TODO: fix... */
    camera->size_half_camera.width = size_camera.width / 2;
    camera->size_half_camera.height = size_camera.height / 2;

    /* TODO: fix... */
    camera->position_deadzone.x = camera->size_half_camera.width - 100;
    camera->position_deadzone.y = camera->size_half_camera.height - 100;

    camera->size_deadzone = (size_2d_t){200, 200};

    /* TODO: fix... */
    camera->size_half_target.width = size_target.width / 2;
    camera->size_half_target.height = size_target.height / 2;

    camera->velocity_pan = 5;
    
    /* Zoom */
    camera->zoom_scale = 1;
    camera->zoom_scale_target = 1;
    camera->zoom_vel = 0;

    /* Shake */
    camera->shake_duration = 0.0f;
    camera->shake_intensity = 0;

    /* Rotation */
    camera->rotation_degrees = 0;

    srand(time(0)); /* TODO: move to random specific source code */

    return camera;
}

/*
static inline uint_t 
lerp(float_t a, float_t b, float_t t)
{
    return a + t * (b - a);
}
*/

inline void
camera_update(camera_t *camera, vector_2d_t target_position, float_t dt)
{
    /*
    static float_t smooth_factor = 0.125;

    transform_2d_t desired_position = {
        target_position.x + 10, 
        target_position.y + 10};

    transform_2d_t smooth_position = {
        lerp(target_position.x, desired_position.x, smooth_factor), 
        lerp(target_position.y, desired_position.y, smooth_factor)};

    camera->x = smooth_position.x - camera->w_half + camera->target_w_half;
    camera->y = smooth_position.y - camera->h_half + camera->target_h_half;        
    */

    /* Zoom camera */
    if (camera->zoom_scale != camera->zoom_scale_target) {
        if (camera->zoom_scale > camera->zoom_scale_target) {
            /* Zoom out */
            camera->zoom_scale += -1.0f * dt; /* TODO: zoom velocity */
            if (camera->zoom_scale < camera->zoom_scale_target) { camera->zoom_scale = camera->zoom_scale_target; }
        } else {
            /* Zoom in */
            camera->zoom_scale += 1.0f * dt; /* TODO: zoom velocity */
            if (camera->zoom_scale > camera->zoom_scale_target) { camera->zoom_scale = camera->zoom_scale_target; }
        }
    }

    /* Translate camera */
    camera->position_camera.x = target_position.x - (float_t)(camera->size_half_camera.width + camera->size_half_target.width);
    camera->position_camera.y = target_position.y - (float_t)(camera->size_half_camera.height + camera->size_half_target.height);

    if (camera->position_camera.x < camera->position_min_camera.x) {
        camera->position_camera.x = camera->position_min_camera.x;
    } else if (camera->position_camera.x > camera->position_max_camera.x) {
        camera->position_camera.x = camera->position_max_camera.x;
    }

    if (camera->position_camera.y < camera->position_min_camera.y) { 
        camera->position_camera.y = camera->position_min_camera.y;
    } else if (camera->position_camera.y > camera->position_max_camera.y) {
        camera->position_camera.y = camera->position_max_camera.y;
    }

    /* Shake camera */
    if (camera->shake_duration > 0.0f) {
        camera->position_camera.x += (rand() % 2 ? 1 : -1) * (int)(rand() % camera->shake_intensity); /* TODO: use random specific source code */
        camera->position_camera.y += (rand() % 2 ? 1 : -1) * (int)(rand() % camera->shake_intensity); /* TODO: use random specific source code */
        camera->shake_duration -= dt;
    }    

    glPopMatrix();
    glPushMatrix();
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    float_t center_x = camera->size_camera.width/2.0f;
    float_t center_y = camera->size_camera.height/2.0f;

    /* Center screen, rotate, scale, return screen to original position */
    glTranslatef(center_x, center_y, 0.0f);
    glRotatef(camera->rotation_degrees, 0.0f, 0.0f, 1.0f);
    glScalef(camera->zoom_scale, camera->zoom_scale, 0.0f);
    glTranslatef(-center_x, -center_y, 0.0f);
}

inline void
camera_set_zoom(camera_t *camera, float_t zoom_scale, float_t zoom_vel)
{
    camera->zoom_scale_target = zoom_scale;
    camera->zoom_vel = zoom_vel;
}

inline void
camera_set_rotate(camera_t *camera, float_t degrees)
{
    camera->rotation_degrees = degrees;
}

inline void
camera_set_shake(camera_t *camera, float_t shake_duration, uint_t shake_intensity)
{
    camera->shake_duration = shake_duration;
    camera->shake_intensity = shake_intensity;
}

#endif