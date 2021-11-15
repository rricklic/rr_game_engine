#ifndef RR_BYTE_BUFFER_H
#define RR_BYTE_BUFFER_H

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "core/rr_api.h"

#define RR_BYTE_BUFFER_DEFAULT_CAPCITY  1024

typedef struct rr_byte_buffer_t
{
    uint8_t *data;      // Buffer that actually holds all relevant byte data // TODO: test as a dynamic array of type uint8_t
    uint32_t size;      // Current size of the stored buffer data
    uint32_t position;  // Current read/write position in the buffer
    uint32_t capacity;  // Current max capacity for the buffer
} rr_byte_buffer_t;

// Generic "write" function for a byte buffer
#define rr_byte_buffer_write(__BB, __T, __VAL)\
do {\
    rr_byte_buffer_t* __BUFFER = __BB;\
    size_t __SZ = sizeof(__T);\
    size_t __TWS = __BUFFER->position + __SZ;\
    if (__TWS >= (size_t)__BUFFER->capacity) {\
        size_t __CAP = __BUFFER->capacity * 2;\
        while(__CAP < __TWS)\
        {\
            __CAP *= 2;\
        }\
        rr_byte_buffer_resize(__BUFFER, __CAP);\
    }\
    *(__T*)(__BUFFER->data + __BUFFER->position) = __VAL;\
    __BUFFER->position += (uint32_t)__SZ;\
    __BUFFER->size += (uint32_t)__SZ;\
} while (0)

// Generic "read" function
#define rr_byte_buffer_read(__BUFFER, __T, __VAL_P)\
do {\
    __T* __V = (__T*)(__VAL_P);\
    rr_byte_buffer_t *__BB = (__BUFFER);\
    *(__V) = *(__T*)(__BB->data + __BB->position);\
    __BB->position += sizeof(__T);\
} while (0)

/*
// Defines variable and sets value from buffer in place
// Use to construct a new variable
#define gs_byte_buffer_readc(__BUFFER, __T, __NAME)\
    __T __NAME = gs_default_val();\
    gs_byte_buffer_read((__BUFFER), __T, &__NAME);

#define gs_byte_buffer_read_bulkc(__BUFFER, __T, __NAME, __SZ)\
    __T __NAME = gs_default_val();\
    __T* gs_macro_cat(__NAME, __LINE__) = &(__NAME);\
    gs_byte_buffer_read_bulk(__BUFFER, (void**)&gs_macro_cat(__NAME, __LINE__), __SZ);
*/

/* Desc */
RR_API_DECL void rr_byte_buffer_init(rr_byte_buffer_t *buffer);

/* Desc */
RR_API_DECL rr_byte_buffer_t rr_byte_buffer_new();

/* Desc */
RR_API_DECL void rr_byte_buffer_free(rr_byte_buffer_t *buffer);

/* Desc */
RR_API_DECL void rr_byte_buffer_clear(rr_byte_buffer_t *buffer);

/* Desc */
RR_API_DECL void rr_byte_buffer_resize(rr_byte_buffer_t *buffer, size_t size);

/* Desc */
RR_API_DECL void rr_byte_buffer_seek_to_beg(rr_byte_buffer_t *buffer);

/* Desc */
RR_API_DECL void rr_byte_buffer_seek_to_end(rr_byte_buffer_t *buffer);

/* Desc */
RR_API_DECL void rr_byte_buffer_advance_position(rr_byte_buffer_t *buffer, size_t size);

/* Desc */
RR_API_DECL void rr_byte_buffer_write_str(rr_byte_buffer_t *buffer, const char *str);                   // Expects a null terminated string

/* Desc */
RR_API_DECL void rr_byte_buffer_read_str(rr_byte_buffer_t *buffer, char *str);                          // Expects an allocated string

/* Desc */
RR_API_DECL void rr_byte_buffer_write_bulk(rr_byte_buffer_t *buffer, void *src, size_t size);

/* Desc */
RR_API_DECL void rr_byte_buffer_read_bulk(rr_byte_buffer_t *buffer, void **dst, size_t size);

/* Desc */
// TODO:
//GS_API_DECL int gs_byte_buffer_write_to_file(gs_byte_buffer_t* buffer, const char* output_path);  // Assumes that the output directory exists

/* Desc */
// TODO:
//GS_API_DECL int gs_byte_buffer_read_from_file(gs_byte_buffer_t* buffer, const char* file_path);   // Assumes an allocated byte buffer

/* Desc */
RR_API_DECL void rr_byte_buffer_memset(rr_byte_buffer_t *buffer, uint8_t val);

void
rr_byte_buffer_init(rr_byte_buffer_t *buffer)
{
    buffer->data = (uint8_t *)rr_malloc(RR_BYTE_BUFFER_DEFAULT_CAPCITY);
    buffer->capacity = RR_BYTE_BUFFER_DEFAULT_CAPCITY;
    buffer->size = 0;
    buffer->position = 0;
}

rr_byte_buffer_t
rr_byte_buffer_new()
{
    rr_byte_buffer_t buffer;
    rr_byte_buffer_init(&buffer);
    return buffer;
}

void
rr_byte_buffer_free(rr_byte_buffer_t *buffer)
{
    if (buffer) {
        rr_free(buffer->data);
    }
}

void
rr_byte_buffer_clear(rr_byte_buffer_t *buffer)
{
    buffer->size = 0;
    buffer->position = 0;   
}

void
rr_byte_buffer_resize(rr_byte_buffer_t *buffer, size_t size)
{
    uint8_t *data = (uint8_t *)rr_realloc(buffer->data, size);
    if (data == NULL) {
        return; // TODO: indicate failure
    }

    buffer->data = data;
    buffer->capacity = (uint32_t)size;
}

void
rr_byte_buffer_seek_to_beg(rr_byte_buffer_t *buffer)
{
    buffer->position = 0;
}

void
rr_byte_buffer_seek_to_end(rr_byte_buffer_t *buffer)
{
    buffer->position = buffer->size;
}

void
rr_byte_buffer_advance_position(rr_byte_buffer_t *buffer, size_t size)
{
    buffer->position += (uint32_t)size; 
}

void
rr_byte_buffer_write_bulk(rr_byte_buffer_t *buffer, void *src, size_t size)
{
    // Check for necessary resize
    size_t new_size = buffer->position + size;
    if (new_size >= (size_t)buffer->capacity) { // TODO: check if equal-to is necessary
        size_t capacity = buffer->capacity * 2;
        while(capacity <= new_size) {
            capacity *= 2;
        }
        rr_byte_buffer_resize(buffer, capacity);
    } 

    // memcpy data
    memcpy((buffer->data + buffer->position), src, size);

    buffer->size += (uint32_t)size;
    buffer->position += (uint32_t)size;
}

void
rr_byte_buffer_read_bulk(rr_byte_buffer_t *buffer, void **dst, size_t size)
{
    memcpy(*dst, (buffer->data + buffer->position), size);
    buffer->position += (uint32_t)size;
}

RR_FORCE_INLINE uint32_t 
rr_string_length(const char *str)
{
    uint32_t size = 0;
    while (str != NULL && str[size] != '\0') {
        size++;
    }
    return size;
}

void
rr_byte_buffer_write_str(rr_byte_buffer_t *buffer, const char *str)
{
    // Write size of string
    uint32_t str_len = rr_string_length(str);
    rr_byte_buffer_write(buffer, uint16_t, str_len);

    size_t i; 
    for (i = 0; i < str_len; ++i) {
        rr_byte_buffer_write(buffer, uint8_t, str[i]);
    }
}

void
rr_byte_buffer_read_str(rr_byte_buffer_t *buffer, char *str)
{
    // Read in size of string from buffer
    uint16_t size;
    rr_byte_buffer_read(buffer, uint16_t, &size);

    uint32_t i;
    for (i = 0; i < size; ++i) {
        rr_byte_buffer_read(buffer, uint8_t, &str[i]);
    }
    str[i] = '\0';
}

/*
gs_result 
gs_byte_buffer_write_to_file(gs_byte_buffer_t *buffer, const char *output_path)
{
    return gs_platform_write_file_contents(output_path, "wb", buffer->data, buffer->size);
}

gs_result 
gs_byte_buffer_read_from_file(gs_byte_buffer_t *buffer,  const char *file_path)
{
    if (!buffer) {
        return 1;
    }

    if (buffer->data) {
        gs_byte_buffer_free(buffer);
    }

    buffer->data = (uint8_t*)gs_platform_read_file_contents(file_path, "rb", (size_t*)&buffer->size);
    if (!buffer->data) {
        gs_assert(false);   
        return 1;
    }

    buffer->position = 0;
    buffer->capacity = buffer->size;
    return 0;
}
*/

RR_API_DECL void
rr_byte_buffer_memset(rr_byte_buffer_t *buffer, uint8_t val)
{
    memset(buffer->data, val, buffer->capacity);
}

#endif