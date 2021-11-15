#ifndef RR_QUEUE_H
#define RR_QUEUE_H

typedef struct rr_queue_t *rr_queue_t;

rr_queue_t
rr_queue_create(void);

void *
rr_queue_enqueue(rr_queue_t rr_queue, void *data);

void *
rr_queue_dequeue(rr_queue_t rr_queue, void *data);

void *
rr_queue_peek(rr_queue_t rr_queue);

unsigned int
rr_queue_length(rr_queue_t rr_queue);

void
rr_queue_foreach(rr_queue_t rr_queue, void(* func)(void *data, void *user_data), void *user_data);

void
rr_queue_destroy(rr_queue_t rr_queue);

#endif