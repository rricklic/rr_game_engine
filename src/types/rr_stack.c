#include <glib.h>

#include "rr_stack.h"

struct rr_stack_t {
    void *impl;
};

rr_stack_t
rr_stack_create(void)
{
    rr_stack_t rr_stack;
    rr_stack = malloc(sizeof(*rr_stack));
    if (rr_stack == NULL) {
        return NULL;
    }

    rr_stack->impl = g_queue_new();
    if (rr_stack->impl == NULL) {
        free(rr_stack);
        return NULL;
    }

    return rr_stack;
}

void *
rr_stack_push(rr_stack_t rr_stack, void *data)
{
    g_queue_push_head(rr_stack->impl, data);
}

void *
rr_stack_pop(rr_stack_t rr_stack, void *data)
{
    return g_queue_pop_head(rr_stack->impl);
}

void *
rr_stack_peek(rr_stack_t rr_stack)
{
    return g_queue_peek_head(rr_stack->impl);
}

unsigned int
rr_stack_length(rr_stack_t rr_stack)
{
    return g_queue_get_length(rr_stack->impl);
}

void
rr_stack_foreach(rr_stack_t rr_stack, void(* func)(void *data, void *user_data), void *user_data)
{
    g_queue_foreach(rr_stack->impl, func, user_data);
}

void
rr_stack_destroy(rr_stack_t rr_stack)
{
    if (rr_stack) {
        g_queue_free(rr_stack->impl);
        free(rr_stack);
    }
}