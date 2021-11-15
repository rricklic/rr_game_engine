#ifndef RR_DYNAMIC_ARRAY_H
#define RR_DYNAMIC_ARRAY_H

#include <types/types_basic.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "core/rr_api.h"

/**
 * 
 * Dynamic array 
 * TODO: realloc down
 * 
 */
typedef struct rr_dynamic_array_header_t {
    uint_t size;
    uint_t capacity;
} rr_dynamic_array_header_t;

#define rr_dynamic_array_header(ARRAY) \
    ((rr_dynamic_array_header_t *)((uint8_t *)(ARRAY) - sizeof(rr_dynamic_array_header_t)))

#define rr_dynamic_array_size(ARRAY) \
    (ARRAY == NULL ? 0 : rr_dynamic_array_header((ARRAY))->size)

#define rr_dynamic_array_capacity(ARRAY) \
    (ARRAY == NULL ? 0 : rr_dynamic_array_header((ARRAY))->capacity)

#define rr_dynamic_array_is_full(ARRAY) \
    ((rr_dynamic_array_size((ARRAY)) == rr_dynamic_array_capacity((ARRAY))))    

RR_INLINE void *
rr_dynamic_array_resize_impl(void *array, size_t size, size_t amount) 
{
    size_t capacity = array ? amount : 0;

    // Create new rr_dynamic_array_header_t with just the header information
    rr_dynamic_array_header_t *header = 
        (rr_dynamic_array_header_t *)rr_realloc(array ? rr_dynamic_array_header(array) : 0, capacity * size + sizeof(rr_dynamic_array_header_t));

    if (!header) {
        return NULL;
    }

    if (!array) {
        header->size = 0;
    }
    header->capacity = (uint_t)capacity;
    return ((uint_t *)header + 2);
}

#define rr_dynamic_array_need_grow(ARRAY, N) \
    ((ARRAY) == 0 || rr_dynamic_array_size(ARRAY) + (N) >= rr_dynamic_array_capacity(ARRAY))

#define rr_dynamic_array_grow(ARRAY) \
    rr_dynamic_array_resize_impl((ARRAY), sizeof(*(ARRAY)), rr_dynamic_array_capacity(ARRAY) ? rr_dynamic_array_capacity(ARRAY) * 2 : 1)

#define rr_dynamic_array_grow_size(ARRAY, SIZE) \
    rr_dynamic_array_resize_impl((ARRAY), (SIZE), rr_dynamic_array_capacity(ARRAY) ? rr_dynamic_array_capacity(ARRAY) * 2 : 1)

RR_FORCE_INLINE void **
rr_dynamic_array_init(void **arr, size_t val_len)
{
    if (*arr == NULL) {
        rr_dynamic_array_header_t *data = 
            (rr_dynamic_array_header_t *)rr_malloc(val_len + sizeof(rr_dynamic_array_header_t));  // Allocate capacity of one
        data->size = 0;
        data->capacity = 1;
        *arr = ((uint_t *)data + 2);
        return arr;
    }
    return NULL;
}

RR_FORCE_INLINE void
rr_dynamic_array_push_data(void **arr, void *val, size_t val_len)
{
    if (*arr == NULL) {
        rr_dynamic_array_init(arr, val_len);
    }
    if (rr_dynamic_array_need_grow(*arr, 1)) {
        uint_t capacity = rr_dynamic_array_capacity(*arr) * 2;

        // Create new rr_dynamic_array_t with just the header information
        rr_dynamic_array_header_t *data = 
            (rr_dynamic_array_header_t *)rr_realloc(rr_dynamic_array_header(*arr), capacity * val_len + sizeof(rr_dynamic_array_header_t));

        if (data) {
            data->capacity = capacity;
            *arr = ((uint_t *)data + 2);
        }
    }
    size_t offset = rr_dynamic_array_size(*arr);
    memcpy(((byte_t *)(*arr)) + offset * val_len, val, val_len);
    rr_dynamic_array_header(*arr)->size++;
}

RR_FORCE_INLINE void
rr_dynamic_array_set_data_i(void **arr, void *val, size_t val_len, uint_t offset)
{
    memcpy(((char *)(*arr)) + offset * val_len, val, val_len);
}

#define rr_dynamic_array_push(ARRAY, VAL) \
    do { \
        rr_dynamic_array_init((void **)&(ARRAY), sizeof(*(ARRAY))); \
        if (!(ARRAY) || ((ARRAY) && rr_dynamic_array_need_grow(ARRAY, 1))) { \
            *((void **)&(ARRAY)) = rr_dynamic_array_grow(ARRAY); \
        } \
        (ARRAY)[rr_dynamic_array_size(ARRAY)] = (VAL); \
        rr_dynamic_array_header(ARRAY)->size++; \
    } while(0)

#define rr_dynamic_array_reserve(ARRAY, AMOUNT) \
    do { \
        if ((!ARRAY)) { \
            rr_dynamic_array_init((void **)&(ARRAY), sizeof(*(ARRAY))); \
        } \
        if ((!ARRAY) || (size_t)AMOUNT > rr_dynamic_array_capacity(ARRAY)) { \
            *((void **)&(ARRAY)) = rr_dynamic_array_resize_impl(ARRAY, sizeof(*ARRAY), AMOUNT); \
        } \
    } while(0)

#define rr_dynamic_array_is_empty(ARRAY) \
    (rr_dynamic_array_init((void **)&(ARRAY), sizeof(*(ARRAY))), (rr_dynamic_array_size(ARRAY) == 0))

#define rr_dynamic_array_pop(ARRAY) \
    do { \
        if (ARRAY && !rr_dynamic_array_is_empty(ARRAY)) { \
            rr_dynamic_array_header(ARRAY)->size -= 1; \
        } \
    } while (0)

#define rr_dynamic_array_last_element(ARRAY) \
    *(ARRAY + (rr_dynamic_array_size(ARRAY) ? rr_dynamic_array_size(ARRAY) - 1 : 0))

// TODO: test performance
#define rr_dynamic_array_foreach(ELEMENT, ARRAY) \
    for(size_t __CONT = 1, __INDEX = 0; \
        __CONT && __INDEX != rr_dynamic_array_size(ARRAY); \
        __CONT = !__CONT, __INDEX++) \
        for(ELEMENT = *((ARRAY) + __INDEX); __CONT; __CONT = !__CONT)

// TODO: This implementation will never iterate over last element in array
#define rr_dynamic_array_for_all_but_last(ARRAY, T, ITER) \
    for (T * ITER = ARRAY; ITER != rr_dynamic_array_last_element(ARRAY); ++ITER)
    
#define rr_dynamic_array_new(T) \
    ((T *)rr_dynamic_array_resize_impl(NULL, sizeof(T), 0))

#define rr_dynamic_array_clear(ARRAY) \
    do { \
        if (ARRAY) { \
            rr_dynamic_array_header(ARRAY)->size = 0; \
        } \
    } while (0)

#define rr_dynamic_array(T) T *

#define rr_dynamic_array_free(ARRAY) \
    do { \
        if (ARRAY) { \
            rr_free(rr_dynamic_array_header(ARRAY)); \
            (ARRAY) = NULL; \
        } \
    } while (0)

#endif