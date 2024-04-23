/*
** EPITECH PROJECT, 2024
** C-Project-Template
** File description:
** env
*/

#include "env.h"

static list_t environement;

env_t get_env_var(const char *key)
{
    list_t current = environement;

    if (!current)
        return NULL;
    for (; current->prev; current = current->prev);
    for (; current; current = current->next)
        if (!strncmp(((env_t)current->data)->name, key, ENV_KEY_SIZE))
            return (env_t)current->data;
    return NULL;
}

void* get_env(const char* key)
{
    env_t current = get_env_var(key);

    if (!current)
        return NULL;
    return current->value;
}

void  set_env(const char* key, void* value)
{
    env_t new_val = (env_t)f_malloc(sizeof(_env_t));
    env_t old_var = getenvvar(key);

    if (!old_var) {
        strncpy(new_val->name, key, ENV_KEY_SIZE);
        mlist_add_at_pos(&environement, mlists_create(new_val), LAST);
    } else {
        f_free(new_val);
        old_var->value = value;
    }
}

void del_env(const char *key, void(*free_function)(void *))
{
    env_t obj = get_env_var(key);

    if (!obj)
        return;
    if (free_function)
        free_function(obj->value);
    f_free(obj);
}

void clear_env(void(*free_function)(void *))
{
    list_t current = environement;

    for (; current->prev; current = current->prev);
    for (; current->next; current = current->next) {
        if (!current->prev)
            continue;
        if (free_function)
            free_function(((env_t)current->prev->data)->value);
        f_free(current->prev);
    }
    if (current->prev) {
        if (free_function)
            free_function(((env_t)current->prev->data)->value);
        f_free(current->prev);
    }
    if (free_function)
        free_function(((env_t)current->data)->value);
    f_free(current);
}