#ifndef RR_LIST_H
#define RR_LIST_H
/**
 * list access - index
 * number of list elements - length
 * list max capacity - capacity
 * list memory consumption/allocation - size
 */ 

typedef struct rr_list_t *rr_list_t;

rr_list_t
rr_list_create(void);

void *
rr_list_insert(rr_list_t rr_list, void *data, unsigned int index);

void *
rr_list_prepend(rr_list_t rr_list, void *data);

void *
rr_list_append(rr_list_t rr_list, void *data);

unsigned int
rr_list_length(rr_list_t rr_list);

void *
rr_list_get(rr_list_t rr_list, unsigned int index);

void *
rr_list_first(rr_list_t rr_list);

void *
rr_list_last(rr_list_t rr_list);

void *
rr_list_remove(rr_list_t rr_list, void *data);

void *
rr_list_remove_index(rr_list_t rr_list, unsigned int index);

void
rr_list_foreach(rr_list_t rr_list, void(* func)(void *data, void *user_data), void *user_data);

void
rr_list_destroy(rr_list_t rr_list);

#endif