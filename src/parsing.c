/*
** EPITECH PROJECT, 2024
** Panoramix
** File description:
** parsing
*/

#include "includes.h"

size_t get_nbr(const char *data)
{
    size_t output = 0;
    const char *tmp = data;

    if (data[0] == '-') {
        tmp = &data[1];
        output = NEGATIVE_NUMBER;
    }
    for (int i = 0; tmp[i]; i++)
        if (strchr("0123456789", tmp[i]) == NULL)
            return INVALID_NUMBER;
    if (output == NEGATIVE_NUMBER)
        return NEGATIVE_NUMBER;
    return (size_t)atoll(data);
}

int usage(const char *filename, const char *error_message, int err_code)
{
    printf("USAGE: %s <nb_villagers> <pot_size> <nb_fights> <nb_refills>\n",
        filename);
    if (strlen(error_message))
        fprintf(stderr, "%s\n", error_message);
    return err_code;
}
