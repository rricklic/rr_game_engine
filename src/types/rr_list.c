#include <glib.h>

#include "rr_list.h"

struct rr_list_t {
    void *impl;
};

rr_list_t
rr_list_create(void)
{
    rr_list_t rr_list;

    rr_list = malloc(sizeof(*rr_list));
    if (rr_list == NULL) {
        return NULL;
    }

    rr_list->impl = NULL;

    return rr_list;
}

void *
rr_list_insert(rr_list_t rr_list, void *data, unsigned int index)
{
    rr_list->impl = g_list_insert(rr_list->impl, data, index);
    return rr_list->impl;
}

void *
rr_list_prepend(rr_list_t rr_list, void *data)
{
    rr_list->impl = g_list_prepend(rr_list->impl, data);
    return rr_list->impl;    
}

void *
rr_list_append(rr_list_t rr_list, void *data)
{
    rr_list->impl = g_list_append(rr_list->impl, data);
    return rr_list->impl;
}

unsigned int
rr_list_length(rr_list_t rr_list)
{
    return g_list_length(rr_list->impl);
}

void *
rr_list_get(rr_list_t rr_list, unsigned int index)
{
    return g_list_nth_data(rr_list->impl, index);
}

void *
rr_list_first(rr_list_t rr_list)
{
    return g_list_first(rr_list->impl);
}

void *
rr_list_last(rr_list_t rr_list)
{
    return g_list_last(rr_list->impl);
}

void *
rr_list_remove(rr_list_t rr_list, void *data)
{
    return g_list_remove(rr_list->impl, data);
}

void *
rr_list_remove_index(rr_list_t rr_list, unsigned int index)
{
    return g_list_remove(rr_list->impl, rr_list_get(rr_list, index));
}

void
rr_list_foreach(rr_list_t rr_list, void (*func)(void *data, void *user_data), void *user_data)
{
    g_list_foreach(rr_list->impl, func, user_data);
}

void
rr_list_destroy(rr_list_t rr_list)
{
    if (rr_list) {
        g_list_free(rr_list->impl);
        free(rr_list);
    }
}