/*
** EPITECH PROJECT, 2024
** Panoramix
** File description:
** garbage
*/

#ifndef INCLUDED_GARBAGE_H
    #define INCLUDED_GARBAGE_H

    #include "headers.h"

typedef struct _garbage_list {
    struct _garbage_list *prev;
    void *ptr;
    struct _garbage_list *next;
} _garbage_t;

typedef _garbage_t *garbage_t;

void *f_malloc(size_t size);
void f_free(void *ptr);
void f_free_ref(void *ptr);
void f_cleanup(void);

    #define FREE __attribute__((cleanup(f_free_ref)))

#endif
