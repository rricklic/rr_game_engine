#ifndef RR_CAMERA_H
#define RR_CAMERA_H

#ifdef DO_NOT_COMPILE

#include "physics/vector_2d.h"
#include "physics/size_2d.h"
#include "types/types_basic.h"

#define CAMERA_ROTATE_CLOCKWISE 0
#define CAMERA_ROTATE_COUNTER_CLOCKWISE 1

/**
 * https://www.youtube.com/watch?v=tu-Qe66AvtY
 * www.essentialmath.com
 *  
 *   lazy-follow (asymptotic averaging smoothing/cubic Hermite curves), look-ahead, lock to axis/platform
 *   framing
 *   voronoi split-screen - split screen only when necessary
 *      display 1 screen if all assets can fix within tolerance
 *      otherwise calculate halfway point, make perpendicular split edge
 *      move screens/regions apart and composite them together (using a stencile)
 *      center players in their respective screen/region
 *      feather the recentering when splitting and combining
 *   screen shake (2D - transitional and rotational)
 *   hand-held camera effect
 *   handle horizontal and verticle differently; or ever upward vs downward or left vs right differently
 *   focus on points of interest/focus 
 *          (too_far_threshold, close_threshold, point_proximity, importance: weight = proximity * importance)
 *      player
 *      locked on enemy
 *      hidden door
 *      treasure/power-up/buttons/levers/traps
 */

/**
 * target position/scale/rotation
 * speed to snap/follow (0, 1]
 * 
 * TODO:
 * XXXX pan
 * XXXX shake
 * track single/multipler
 * XXXX zoom
 * XXXX rotate
 * spin
  * deadzone (prevent camera movement)
 * smooth following - trail behind and smoothly "center" target
 * look ahead
 * snap to ground/ceiling/platform
 */ 

typedef struct camera_t {
/*
vector_2d_t size;
vector_2d_t position;
*/

    /* Translation */
    vector_2d_t position_camera;
    /* TODO: target position */
    sint_t velocity_pan;

    /* Ranges */
    vector_2d_t position_min_camera;
    vector_2d_t position_max_camera;
    size_2d_t size_camera;
    size_2d_t size_half_camera;

    /* Deadzone */ 
    vector_2d_t position_deadzone;
    size_2d_t size_deadzone;

    /* Target */
    size_2d_t size_half_target;

    /* Zoom */
    float_t zoom_scale;
    float_t zoom_scale_target;
    float_t zoom_vel;

    /* Shake */
    float_t shake_duration;
    uint_t shake_intensity;

    /* Rotation */
    float_t rotation_degrees;
    /* TODO: target rotation */
    /* TODO: rotation velocity */

    float_t trauma;
} camera_t;

void
camera_free(camera_t *camera);

camera_t *
camera_create(
    vector_2d_t position_camera, 
    size_2d_t size_camera, 
    vector_2d_t position_camera_min, 
    vector_2d_t position_camera_max, 
    size_2d_t size_target_camera);

void
camera_update(camera_t *camera, vector_2d_t target_position, float_t dt);

void
camera_set_zoom(camera_t *camera, float_t zoom_scale, float_t zoom_vel);

void
camera_set_shake(camera_t *camera, float_t shake_duration, uint_t shake_intensity);

void
camera_set_rotate(camera_t *camera, float_t degrees /*int direction, float_t rotate_vel*/);

#endif

#endif