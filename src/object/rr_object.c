#include "rr_object.h"

rr_object_t *
rr_object_create(float_t x, float_t y)
{
    rr_object_t *rr_object;

    rr_object = malloc(sizeof(*rr_object));
    if (rr_object == NULL) {
        return NULL;
    }

    rr_object->position = (vector_2d_t){x, y};

    return rr_object;
}

void 
rr_object_destroy(rr_object_t *rr_object)
{
    free(rr_object);
}