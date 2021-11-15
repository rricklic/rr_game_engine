#include <glib.h>

#include "rr_map.h"

struct rr_map_t {
    void *impl;
};

rr_map_t
rr_map_create(void)
{
    rr_map_t rr_map;
    rr_map = malloc(sizeof(*rr_map));
    if (rr_map == NULL) {
        return NULL;
    }

    rr_map->impl = g_hash_table_new(g_direct_hash, g_direct_equal);
    if (rr_map->impl == NULL) {
        free(rr_map);
        return NULL;
    }

    return rr_map;
}

rr_map_t
rr_map_create_full(
    int (*key_hash_func)(void *key),
    int (*key_equal_func)(void *key1, void *key2), 
    void (*key_destroy_func)(void *key), 
    void (*value_destroy_func)(void *value))
{
    rr_map_t rr_map;
    rr_map = malloc(sizeof(*rr_map));
    if (rr_map == NULL) {
        return NULL;
    }

    rr_map->impl = g_hash_table_new_full(key_hash_func, key_equal_func, key_destroy_func, value_destroy_func);
    if (rr_map->impl == NULL) {
        free(rr_map);
        return NULL;
    }

    return rr_map;
}

int
rr_map_put(rr_map_t rr_map, void *key, void *value)
{
    return g_hash_table_insert((GHashTable *)rr_map->impl, key, value);
}

int
rr_map_remove_key(rr_map_t rr_map, void *key)
{
    return g_hash_table_remove((GHashTable *)rr_map->impl, key);
}

void
rr_map_clear(rr_map_t rr_map)
{
    return g_hash_table_remove_all((GHashTable *)rr_map->impl);
}

int
rr_map_length(rr_map_t rr_map)
{
    return g_hash_table_size((GHashTable *)rr_map->impl);
}

void *
rr_map_get(rr_map_t rr_map, void *key)
{
    return g_hash_table_lookup((GHashTable *)rr_map->impl, key);
}

void *
rr_map_get_keys(rr_map_t rr_map, unsigned int *length)
{
    return g_hash_table_get_keys_as_array((GHashTable *)rr_map->impl, length);
}

void *
rr_map_get_values(rr_map_t rr_map)
{
    return g_hash_table_get_values((GHashTable *)rr_map->impl);
}

void
rr_map_foreach(rr_map_t rr_map, void(*func)(void *, void *, void *), void *user_data)
{
    g_hash_table_foreach((GHashTable *)rr_map->impl, func, user_data);
}

void
rr_map_foreach_remove(rr_map_t rr_map, void(*func)(void *, void *, void *), void *user_data)
{
    g_hash_table_foreach_remove((GHashTable *)rr_map->impl, func, user_data);
}

/* TODO:
void
rr_map_set_value_destroy_func(rr_map_t rr_map, void(*func)(void *data))
{
    g_map_set_(rr_map->impl, func);
}

void
rr_map_set_value_compare_func(rr_map_t rr_map, void(*func)(void *data))
{
    g_map_set_(rr_map->impl, func);
}
*/

void
rr_map_destroy(rr_map_t rr_map)
{
    if (rr_map) {
        g_hash_table_destroy((GHashTable *)rr_map->impl);
        free(rr_map);
    }
}