#include <stdlib.h>
#include <stdio.h>

#include "adt_example.h"

typedef struct adt_t {
    int x;
    int y;
} adt_t;

adt_ptr_t
adt_create(void)
{
    adt_t *adt = malloc(sizeof(adt_t));
    if (!adt) {
        return NULL;
    }
    adt->x = 0;
    adt->y = 0;
    return adt;
}

void
adt_set(adt_ptr_t adt_ptr, int x, int y)
{
    adt_ptr->x = x;
    adt_ptr->y = y;
}

void
adt_print(adt_ptr_t adt_ptr)
{
    printf("x=%d, y=%d\n", adt_ptr->x, adt_ptr->y);
}

void
adt_destroy(adt_ptr_t adt_ptr)
{
    free(adt_ptr);
}

struct adt2_t {
    int a;
    int b;
};

adt2_t *
adt2_create(void)
{
    adt2_t *adt2 = malloc(sizeof(adt2_t));
    if (!adt2) {
        return NULL;
    }
    adt2->a = 0;
    adt2->b = 0;
    return adt2;
}

void
adt2_set(adt2_t *adt2, int a, int b)
{
    adt2->a = a;
    adt2->b = b;
}

void
adt2_print(adt2_t *adt2)
{
    printf("a=%d, b=%d\n", adt2->a, adt2->b);
}

void
adt2_destroy(adt2_t *adt2)
{
    free(adt2);
}