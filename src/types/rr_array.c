#include <glib.h>

#include <stdio.h> /* TODO: REMOVE */

#include "rr_array.h"

struct rr_array_t {
    void *impl;
};

rr_array_t
rr_array_create(unsigned int element_size)
{
    rr_array_t rr_array;
    rr_array = malloc(sizeof(*rr_array));
    if (rr_array == NULL) {
        return NULL;
    }

    rr_array->impl = g_array_new(FALSE, FALSE, element_size);
    if (rr_array->impl == NULL) {
        free(rr_array);
        return NULL;
    }

    return rr_array;
}

void
rr_array_insert(rr_array_t rr_array, unsigned int index, void *data)
{
    g_array_insert_val(rr_array->impl, index, data);
}

void
rr_array_prepend(rr_array_t rr_array, void *data)
{
    g_array_prepend_val(rr_array->impl, data);
}

void
rr_array_append(rr_array_t rr_array, void *data)
{
    g_array_append_val(rr_array->impl, data);
}

void
rr_array_remove_index(rr_array_t rr_array, unsigned int index)
{
    g_array_remove_index_fast(rr_array->impl, index);
}

unsigned int
rr_array_get_length(rr_array_t rr_array)
{
    return ((GArray *)rr_array->impl)->len;
}

/* TODO:
void
rr_array_set_element_destroy_func(rr_array_t rr_array, void(*func)(void *data))
{
    g_array_set_free_func(rr_array->impl, func);
}

void
rr_array_set_element_compare_func(rr_array_t rr_array, void(*func)(void *data))
{
    g_array_set_(rr_array->impl, func);
}
*/

void *
rr_array_get(rr_array_t rr_array, unsigned int index)
{
    /* TODO: replace with the appropriate expanded statement to handle handle other type sizes other than (void *) */
    /*return (((void **) (void *) ((GArray *)rr_array->impl)->data) [(index)]);*/
    return g_array_index((GArray *)rr_array->impl, void *, index); /* TODO: ...*/
}

/* TODO: expose? */
static void *
rr_array_get_data(rr_array_t rr_array)
{
    return rr_array_get(rr_array, 0);
}

void
rr_array_foreach(rr_array_t rr_array, void (*func)(void *data, void *user_data), void *user_data)
{
    /* TODO: access data directly */
    void *data;
    for (int index = 0; index < rr_array_get_length(rr_array); index++) {
        data = rr_array_get(rr_array, index);
        func(data, user_data);
    }
}

void
rr_array_clear(rr_array_t rr_array)
{
    for (int index = rr_array_get_length(rr_array) - 1; index >= 0; index--) {
        rr_array_remove_index(rr_array, index);
    }
}

void
rr_array_destroy(rr_array_t rr_array)
{
    if (rr_array) {
        g_array_free(rr_array->impl, TRUE); /* TRUE means to free each element as well */
        free(rr_array);
    }
}