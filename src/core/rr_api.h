#ifndef RR_API_H
#define RR_API_H

#include <stdlib.h>

/**
 *
 * Visibility
 * TODO: understand when to use what
 * 
 */
#ifndef RR_INLINE
    #define RR_INLINE static inline
#endif

#ifndef RR_LOCAL_PERSIST
    #define RR_LOCAL_PERSIST static
#endif

#ifndef RR_GLOBAL
    #define RR_GLOBAL static
#endif

#if (defined _WIN32 || defined _WIN64)
    #define RR_FORCE_INLINE RR_INLINE
#elif (defined __APPLE__ || defined _APPLE)
    #define RR_FORCE_INLINE static __attribute__((always_inline))
#else
    #define RR_FORCE_INLINE RR_INLINE
#endif

#ifdef __cplusplus
   #define RR_API_DECL   extern "C"
#else
   #define RR_API_DECL   extern
#endif

/**
 *
 * Memory allocation 
 * 
 */
#ifndef rr_malloc
    #define rr_malloc(SIZE) malloc(SIZE)
#endif

#ifndef rr_free
    #define rr_free(PTR) free(PTR)
#endif

#ifndef rr_realloc
    #define rr_realloc(PTR, SIZE) realloc(PTR, SIZE)
#endif

#ifndef rr_calloc
    #define rr_calloc(NUM, SIZE) calloc(NUM, SIZE)
#endif

/* TODO: asset macro - enable/disable */

#endif