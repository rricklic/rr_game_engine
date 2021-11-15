#ifndef RR_TYPES_BASIC_H
#define RR_TYPES_BASIC_H

/* TODO: rename rr_basic_types.h */

#ifdef RR_ENGINE_SDL || RR_ENGINE_SDL_64
    #include <SDL_stdinc.h>
#else
    #include <stdint.h>
#endif

#ifndef byte_t
    #ifdef RR_ENGINE_SDL || RR_ENGINE_SDL_64
        typedef Uint8 byte_t;
    #else
        typedef uint8_t byte_t;
    #endif
#endif

#ifndef uint_t
    #ifdef RR_ENGINE_SDL
        typedef Uint32 uint_t;
    #elif RR_ENGINE_SDL_64
        typedef Uint64 uint_t;
    #elif RR_ENGINE_64
        typedef uint64_t uint_t;
    #else
        typedef uint32_t uint_t;
    #endif
#endif

#ifndef sint_t
    #ifdef RR_ENGINE_SDL
        typedef Sint32 sint_t;
    #elif RR_ENGINE_SDL_64
        typedef Sint64 sint_t;
    #elif RR_ENGINE_64
        typedef int64_t sint_t;
    #else
        typedef int32_t sint_t;
    #endif
#endif

#ifndef float_t
    #ifdef RR_ENGINE_DOUBLE
        typedef double float_t;
    #else
        typedef float float_t;
    #endif
#endif

typedef struct rr_func_t {
    void(*func)(void *);
} rr_func_t;

#endif