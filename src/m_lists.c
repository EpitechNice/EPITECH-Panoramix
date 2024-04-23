/*
** EPITECH PROJECT, 2024
** C-Project-Template
** File description:
** m_lists
*/

#include "m_lists.h"

static void mlists_append(list_t *ref, list_t add, bool add_after)
{
    if (!add)
        return;
    if (!(*ref)) {
        *ref = add;
        return;
    }
    if (add_after) {
        if ((*ref)->next)
            (*ref)->next->prev = add;
        add->next = (*ref)->next;
        add->prev = *ref;
        (*ref)->next = add;
    } else {
        if ((*ref)->prev)
            (*ref)->prev->next = add;
        add->prev = (*ref)->prev;
        add->next = *ref;
        (*ref)->prev = add;
    }
}

static void mlist_set_first(list_t *ref, list_t add)
{
    for (; (*ref)->prev; *ref = (*ref)->prev);
    mlists_append(ref, add, false);
}

static void mlist_set_last(list_t *ref, list_t add)
{
    for (; (*ref)->next; *ref = (*ref)->next);
    mlists_append(ref, add, true);
}

list_t mlists_create(void *data)
{
    list_t obj = (list_t)f_malloc(sizeof(_list_t));

    obj->prev = NULL;
    obj->data = data;
    obj->next = NULL;
    return obj;
}

void *mlists_pop(void *data, list_t *ref)
{
    list_t current = *ref;
    void *output;

    if (!current)
        return NULL;
    for (; current->prev; current = current->prev);
    for (; current; current = current->next) {
        if (current->data != data)
            continue;
        if (current == *ref)
            *ref = current->prev ? current->prev : current->next;
        if (current->prev)
            current->prev->next = current->next;
        if (current->next)
            current->next->prev = current->prev;
        output = current->data;
        f_free(current);
        return output;
    }
    return NULL;
}

void mlist_destroy(list_t *ref, void(*free_function)(void *))
{
    list_t current = *ref;

    if (!current)
        return;
    for (; current->prev; current = current->prev);
    for (; current->next; current = current->next) {
        if (!current->prev)
            continue;
        if (free_function)
            free_function(current->prev->data);
        f_free(current->prev);
    }
    if (current->prev) {
        if (free_function)
            free_function(current->prev->data);
        f_free(current->prev);
    }
    if (free_function)
        free_function(current->data);
    f_free(current);
}

size_t mlists_length(list_t ref)
{
    size_t length = 0;
    list_t current = ref;

    if (!current)
        return length;
    for (; current->prev; current = current->prev);
    for (; current; current = current->next)
        length++;
    return length;
}

void mlist_add_at_pos(list_t *ref, list_t add, element_position_t pos)
{
    list_t _ref;

    if (!ref || !add)
        return;
    _ref = *ref;
    if (!_ref) {
        *ref = add;
        return;
    }
    if (pos == FIRST)
        mlist_set_first(&_ref, add);
    if (pos == BEFORE || pos == AFTER)
        mlists_append(&_ref, add, (pos == AFTER));
    if (pos == LAST)
        mlist_set_last(&_ref, add);
}