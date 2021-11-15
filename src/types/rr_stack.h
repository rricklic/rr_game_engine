#ifndef RR_STACK_H
#define RR_STACK_H

typedef struct rr_stack_t *rr_stack_t;

rr_stack_t
rr_stack_create(void);

void *
rr_stack_push(rr_stack_t rr_stack, void *data);

void *
rr_stack_pop(rr_stack_t rr_stack, void *data);

void *
rr_stack_peek(rr_stack_t rr_stack);

unsigned int
rr_stack_length(rr_stack_t rr_stack);

void
rr_stack_foreach(rr_stack_t rr_stack, void(* func)(void *data, void *user_data), void *user_data);

void
rr_stack_destroy(rr_stack_t rr_stack);

#endif