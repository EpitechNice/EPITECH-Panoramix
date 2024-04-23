/*
** EPITECH PROJECT, 2024
** C-Project-Template
** File description:
** list_ts
*/

#ifndef INCLUDED_list_tS_H
    #define INCLUDED_list_tS_H

    #include "garbage.h"

typedef struct _list_s {
    struct _list_s *prev;
    void *data;
    struct _list_s *next;
} _list_t;

typedef _list_t *list_t;

typedef enum {
    // Append the element at the beggining of the list
    FIRST,
    // Append the element just before the reference
    BEFORE,
    // Append the element just after the reference
    AFTER,
    // Append the element at the end of the list
    LAST,
} element_position_t;

/// @brief Create a list "node" form the given pointer
/// @param data Pointer to the list data. Best practice to allocate the pointer
/// @return The newly created list node.
list_t mlists_create(void *data);

/// @brief Remove element of a list. If it's not in the list, return NULL
/// @param data Pointer to remove. Please note that this is a POINTER.
// It means that you cannot remove each element that is strcmp with "no".
/// @param ref Reference to the list
/// @return The pointed object or NULL if not found
void *mlists_pop(void *data, list_t *ref);

/// @brief Whipe out a list
/// @param ref Reference to the list
/// @param free_function If set, used on each element to free it
void mlist_destroy(list_t *ref, void(*free_function)(void *));

/// @brief Get the length of the list
/// @param ref Reference to the list
/// @return The length of the list
size_t mlists_length(list_t ref);

/// @brief append, repend, set_before and set_after
/// @param ref Reference to the list
/// @param new New element to set in the list
/// @param pos Position to set it to (see element_position)
void mlist_add_at_pos(list_t *ref, list_t add, element_position_t pos);

#endif
