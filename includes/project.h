/*
** EPITECH PROJECT, 2024
** Panoramix
** File description:
** project
*/

#ifndef INCLUDED_PROJECT_H
    #define INCLUDED_PROJECT_H

    #define EXIT_SUCCESS 0
    #define EXIT_ERROR 84

    #define NEGATIVE_NUMBER ((size_t)-1)
    #define INVALID_NUMBER ((size_t)-2)

    #define UNUSED __attribute__((unused))

// ===== parsing.c =====

/// @brief Druid thrad
/// @param _village void* pointing to a village_t*
/// @return Nothin
void *druid_thread(void *_village);

// ===== parsing.c =====

/// @brief Display the standard help and return the provided err_code
/// @param filename argv[0]
/// @param error_message Displayed error message (or "")
/// @param err_code The required error code
/// @return err_code
int usage(const char *filename, const char *error_message, int err_code);

/// @brief Retreive number from char *
/// @param data Provided char * to cast into size_t
/// @return NEGATIVE_NUMBER, INVALID_NUMBER or the actual number
size_t get_nbr(const char *data);

// ===== village.c =====

/// @brief Start the entire program, given the 4 args
/// @param args size_t args[4]. Note the 4, do NOT give less
/// @return EXIT_SUCCESS / EXIT_ERROR
int launch_village(size_t *args);

#endif
