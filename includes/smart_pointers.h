/*
** EPITECH PROJECT, 2024
** C-Project-Template
** File description:
** smart_pointers
*/

#ifndef INCLUDED_SMART_POINTERS_H
    #define INCLUDED_SMART_POINTERS_H

    #include "garbage.h"

#if (!defined(__GNUC__))
    #error "Smart pointers require GNU __attribute__ macro !"
#endif

typedef struct {
    size_t size;
    size_t __counter;
    void *data;
} _smart_ptr_t;

typedef _smart_ptr_t *smart_ptr_t;

smart_ptr_t dev_make_ptr(size_t size);
smart_ptr_t share_ptr(smart_ptr_t p);
void dev_smart_ptr_cleanup(void *variable_pointer);

    #define CLEANUP(func) __attribute__((cleanup(func)))
    #define MAKE_PTR(type) dev_make_ptr(sizeof(type))
    #define SHARED_PTR(name) smart_ptr_t name CLEANUP(dev_smart_ptr_cleanup)
    #define GET_PTR(var, type) ((type)var->data)
    #define RET_PTR(ptr) share_ptr(p)

// Usage:
//  SHARED_PTR(p) = MAKE_PTR(int)
//  GET_PTR(p, int) = 12;
//  return RET_PTR(p);

#endif
