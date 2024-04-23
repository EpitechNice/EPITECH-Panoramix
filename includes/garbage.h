/*
** EPITECH PROJECT, 2024
** C-Project-Template
** File description:
** garbage
*/

#ifndef INCLUDED_GARBAGE_H
    #define INCLUDED_GARBAGE_H

    #include "headers.h"

typedef struct _garbage_s {
    struct _garbage_s *prev;
    void *ptr;
    size_t size;
    struct _garbage_s *next;
} _garbage_t;

typedef _garbage_t *garbage_t;

/// @brief Allocate {size} bytes through the garbage collector.
/// @param size Size to be allocated
/// @return Newly allocated pointer, or NULL
void* f_malloc(size_t size);

/// @brief Change the size of the object passed. If size is less that previous,
// do nothing.
/// @param origin Original pointer to be reallocated
/// @param new_size New size of the object
/// @return The new object
void* f_realloc(void* origin, size_t new_size);

/// @brief Free object allocated with the garbage collector.
/// @param ptr Pointer to the object to free
void f_free(void* ptr);

/// @brief Free pointer
/// @param ptr address of a pointer to an object allocated by the gc
void f_free_ref(void* ptr);

/// @brief Free all allocated variables. Automaticly called on gracefull stop
void f_cleanup(void);

    #define FREE    __attribute__((cleanup(f_free_ref)))
    #define UNUSED  __attribute__((unused))
    #define PURE    __attribute__((pure))

#endif
