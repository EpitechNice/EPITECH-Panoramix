/*
** EPITECH PROJECT, 2024
** Panoramix
** File description:
** garbage
*/

#include "garbage.h"

static garbage_t garbage_collector_reference;

static garbage_t f_new(char *ptr)
{
    garbage_t new = (garbage_t)malloc(sizeof(_garbage_t));

    new->prev = NULL;
    new->ptr = ptr;
    new->next = NULL;
    return new;
}

static void f_add(garbage_t new)
{
    garbage_t current = garbage_collector_reference;

    if (!current)
        return;
    for (; current->next; current = current->next);
    current->next = new;
    new->prev = current;
}

void f_cleanup(void)
{
    garbage_t current = garbage_collector_reference;

    if (!garbage_collector_reference)
        return;
    for (; current->prev; current = current->prev);
    for (; current->next; current = current->next) {
        if (!current->prev)
            continue;
        free(current->prev->ptr);
        free(current->prev);
        current->prev = NULL;
    }
    if (current->prev) {
        free(current->prev->ptr);
        free(current->prev);
    }
    free(current->ptr);
    free(current);
    garbage_collector_reference = NULL;
}

void *f_malloc(size_t size)
{
    void *obj = malloc(size);

    for (size_t i = 0; i < size; i++)
        *(char *)(obj + i) = 0;
    if (!garbage_collector_reference)
        garbage_collector_reference = f_new(obj);
    else
        f_add(f_new(obj));
    return obj;
}

void f_free(void *ptr)
{
    garbage_t current = garbage_collector_reference;

    if (!current)
        return;
    for (; current->prev; current = current->prev);
    for (; current; current = current->next) {
        if (current->ptr != ptr)
            continue;
        free(current->ptr);
        if (current == garbage_collector_reference)
            garbage_collector_reference = current->prev ?
                current->prev : current->next;
        if (current->prev)
            current->prev->next = current->next;
        if (current->next)
            current->next->prev = current->prev;
        free(current);
        return;
    }
}

void f_free_ref(void *ptr)
{
    f_free(*(void **)ptr);
}

void __attribute__((destructor)) f_self_cleanup(void)
{
    f_cleanup();
}
