#ifndef RR_MAP_H
#define RR_MAP_H

/**
 * key -> value
 * number of key/value pairs - length
 * map max capacity - capacity
 * map memory consumption/allocation - size
 */

typedef struct rr_map_t *rr_map_t;

rr_map_t
rr_map_create(void);

rr_map_t
rr_map_create_full(
    int (*key_hash_func)(void *key),
    int (*key_equal_func)(void *key1, void *key2), 
    void (*key_destroy_func)(void *key), 
    void (*value_destroy_func)(void *value));

int
rr_map_put(rr_map_t rr_map, void *key, void *value);

int
rr_map_remove_key(rr_map_t rr_map, void *key);

void
rr_map_clear(rr_map_t rr_map);

int
rr_map_length(rr_map_t rr_map);

void *
rr_map_get(rr_map_t rr_map, void *key);

void *
rr_map_get_keys(rr_map_t rr_map, unsigned int *length);

void *
rr_map_get_values(rr_map_t rr_map);

void
rr_map_foreach(rr_map_t rr_map, void(*func)(void *, void *, void *), void *user_data);

void
rr_map_foreach_remove(rr_map_t rr_map, void(*func)(void *, void *, void *), void *user_data);

void
rr_map_destroy(rr_map_t rr_map);

#endif