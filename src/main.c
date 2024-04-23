/*
** EPITECH PROJECT, 2024
** Panoramix
** File description:
** main
*/

#include "includes.h"

int main(int argc, char **argv)
{
    size_t args[4];

    debug("Starting to retreive command line args\n");
    if (argc != 5)
        return usage(argv[0], "", 84);
    for (int i = 1; i < argc; i++) {
        args[i - 1] = get_nbr(argv[i]);
        if (args[i - 1] == NEGATIVE_NUMBER)
            return usage(argv[0], "Values must be >0.", 84);
        if (args[i - 1] == INVALID_NUMBER)
            return usage(argv[0], "Invalid number.", 84);
    }
    info("Starting the village\n");
    return launch_village(args);
}
