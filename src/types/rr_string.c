#include <glib.h>

#include "rr_string.h"

struct rr_string_t {
    void *impl;
    int is_free;
};

/*
    rr_string_t rr_string;

    rr_string = malloc(sizeof(*rr_string));
    if (rr_string == NULL) {
        return NULL;
    }

    rr_string->impl = g_string_new(cstr);
    if (rr_string->impl == NULL) {
        free(rr_string);
        return NULL;
    }

    rr_string->is_free = is_free;
*/

rr_string_t
rr_string_create(char *cstr, int is_free)
{
    rr_string_t rr_string;

    rr_string = malloc(sizeof(*rr_string));
    if (rr_string == NULL) {
        return NULL;
    }

    rr_string->impl = g_string_new(cstr);
    if (rr_string->impl == NULL) {
        free(rr_string);
        return NULL;
    }

    rr_string->is_free = is_free;
}

char
rr_string_charat(rr_string_t rr_string, int index)
{
    return NULL;
}

rr_string_t
rr_string_append(rr_string_t rr_string1, rr_string_t rr_string2)
{
    return g_string_append(rr_string1, rr_string2);
}

rr_string_t
rr_string_prepend(rr_string_t rr_string1, rr_string_t rr_string2)
{
    return g_string_prepend(rr_string1, rr_string2);
}

char *
rr_string_to_cstr(rr_string_t rr_string)
{
    return ((GString *)rr_string->impl)->str;
}

int
rr_string_length(rr_string_t rr_string)
{
    return ((GString *)rr_string->impl)->len;
}

void
rr_string_destroy(rr_string_t rr_string)
{
    if (rr_string) {
        g_string_free(rr_string->impl, rr_string->is_free);
        free(rr_string);
    }
}