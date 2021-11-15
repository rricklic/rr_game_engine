#ifndef RR_STRING_H
#define RR_STRING_H

/**
 * number of chars in string - length
 * string memory consumption/allocation - size
 */

typedef struct rr_string_t *rr_string_t;

rr_string_t
rr_string_create(char *cstr, int is_free);

char
rr_string_charat(rr_string_t string, int index);

rr_string_t
rr_string_append(rr_string_t string1, rr_string_t string2);

rr_string_t
rr_string_prepend(rr_string_t string1, rr_string_t string2);

char *
rr_string_to_cstr(rr_string_t string);

int
rr_string_length(rr_string_t string);

void
rr_string_destroy(rr_string_t string);

#endif