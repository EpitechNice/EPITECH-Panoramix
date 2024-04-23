/*
** EPITECH PROJECT, 2024
** Panoramix
** File description:
** types
*/

#ifndef INCLUDED_TYPES_H
    #define INCLUDED_TYPES_H

    #include "headers.h"

/// @brief Define druid structure : It's pot size, and nb refils
typedef struct {
    size_t _max_pot_size;
    size_t _nb_refills;
    size_t _pot_size;
} druid_t;

/// @brief Define a villager, meaning if he got potion or not
typedef struct {
    bool _got_potion;
    size_t _id;
    size_t _nb_fights_left;
} villager_t;

typedef struct {
    bool _pot_status; // true: have some refills, false: no more reffils
    bool _fight_over;
    size_t _thread_id; // Basicly used as a value as much as a mutex
    // Just did not want to rape my RAM with another pthread_t.
    // Just wait for it to become 

    size_t _nb_villagers;

    druid_t *_druid;
    villager_t **_villagers;

    pthread_t _druid_thread;
    pthread_t *_villagers_thread;

    pthread_mutex_t _pot;
    sem_t _druid_message;
    sem_t _villager_message;
} village_t;

#endif
