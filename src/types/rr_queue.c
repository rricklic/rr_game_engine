#include <glib.h>

#include "rr_queue.h"

struct rr_queue_t {
    void *impl;
};

rr_queue_t
rr_queue_create(void)
{
    rr_queue_t rr_queue;
    rr_queue = malloc(sizeof(*rr_queue));
    if (rr_queue == NULL) {
        return NULL;
    }

    rr_queue->impl = g_queue_new();
    if (rr_queue->impl == NULL) {
        free(rr_queue);
        return NULL;
    }

    return rr_queue;
}

void *
rr_queue_enqueue(rr_queue_t rr_queue, void *data)
{
    g_queue_push_tail(rr_queue->impl, data);
}

void *
rr_queue_dequeue(rr_queue_t rr_queue, void *data)
{
    return g_queue_pop_head(rr_queue->impl);
}

void *
rr_queue_peek(rr_queue_t rr_queue)
{
    return g_queue_peek_head(rr_queue->impl);
}

unsigned int
rr_queue_length(rr_queue_t rr_queue)
{
    return g_queue_get_length(rr_queue);
}

void
rr_queue_foreach(rr_queue_t rr_queue, void(* func)(void *data, void *user_data), void *user_data)
{
    g_queue_foreach(rr_queue->impl, func, user_data);
}

void
rr_queue_destroy(rr_queue_t rr_queue)
{
    if (rr_queue) {
        g_queue_free(rr_queue->impl);
        free(rr_queue);
    }
}