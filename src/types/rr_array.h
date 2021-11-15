#ifndef RR_ARRAY_H
#define RR_ARRAY_H
/**
 * array access - index
 * number of array elements - length
 * array max capacity - capacity
 * array memory consumption/allocation - size
 */ 

typedef struct rr_array_t *rr_array_t;

rr_array_t
rr_array_create(unsigned int element_size);

void
rr_array_insert(rr_array_t rr_array, unsigned int index, void *data);

void
rr_array_prepend(rr_array_t rr_array, void *data);

void
rr_array_append(rr_array_t rr_array, void *data);

void
rr_array_remove_index(rr_array_t rr_array, unsigned int index);

unsigned int
rr_array_get_length(rr_array_t rr_array);

void *
rr_array_get(rr_array_t rr_array, unsigned int index);

/* TODO: */
/*
void *
rr_array_get_data(rr_array_t rr_array, size_t *length);
*/

void
rr_array_foreach(rr_array_t rr_array, void (*func)(void *data, void *user_data), void *user_data);

void
rr_array_clear(rr_array_t rr_array);

void
rr_array_destroy(rr_array_t rr_array);

#endif