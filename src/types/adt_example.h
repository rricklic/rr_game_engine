#ifndef RR_ADT_EXAMPLE_H
#define RR_ADT_EXAMPLE_H

/* Pointer to incomplete type: opaque pointer type */
typedef struct adt_t *adt_ptr_t;

adt_ptr_t
adt_create(void);

void
adt_set(adt_ptr_t adt_ptr, int x, int y);

void
adt_print(adt_ptr_t adt_ptr);

void
adt_destroy(adt_ptr_t adt_ptr);

/* Create typedef of incomplete type */
typedef struct adt2_t adt2_t;

adt2_t *
adt2_create(void);

void
adt2_set(adt2_t *adt2, int a, int b);

void
adt2_print(adt2_t *adt2);

void
adt2_destroy(adt2_t *adt2);

#endif