/*
** EPITECH PROJECT, 2024
** C-Project-Template
** File description:
** env
*/

#ifndef INCLUDED_ENV_H
    #define INCLUDED_ENV_H

    #include "headers.h"
    #include "garbage.h"
    #include "m_lists.h"

    #define ENV_KEY_SIZE 32

typedef struct {
    char name[ENV_KEY_SIZE + 1];
    void *value;
} _env_t;

typedef _env_t *env_t;

/// @brief Get the env_t object associated with a key
/// @param key Key to search for
/// @return The found object, or NULL
env_t get_env_var(const char *key);

/// @brief Get variable in the environement
/// @param key Key to search for
/// @return Pointer to the value retreived, or NULL
void* get_env(const char *key);

/// @brief Set variable in the environement
/// @param key Key to set
/// @param value Value to set
void set_env(const char *key, void *value);

/// @brief Delete an element in the env
/// @param key Key to search for
/// @param free_function Function to be called on the it's value, or NULL
void del_env(const char *key, void(*free_function)(void *));

/// @brief Clear the environement
/// @param free_function Function to be called on each value
void clear_env(void(*free_function)(void *));

#endif
