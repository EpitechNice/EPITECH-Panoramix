/*
** EPITECH PROJECT, 2024
** Panoramix
** File description:
** logging
*/

#include "logging.h"

static void show_hour(FILE* output)
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    if (output == stdout)
        fprintf(output, "\r");
    fprintf(output, "[%02i/%02i/%i %02i:%02i:%02i]", tm.tm_mday, tm.tm_mon
        + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
    fflush(output);
}

void debug(const char *format, ...)
{
    va_list args1;
    va_list args2;

    #ifndef DEBUG
        return;
    #endif
    va_start(args1, format);
    va_copy(args2, args1);
    show_hour(stdout);
    printf(" \033[90m[  DEBUG  ]\033[0m ");
    vprintf(format, args2);
    fflush(stdout);
}

void info(const char *format, ...)
{
    va_list args1;
    va_list args2;

    #ifndef DEBUG
        return;
    #endif
    va_start(args1, format);
    va_copy(args2, args1);
    show_hour(stdout);
    printf(" \033[94m[  INFOS  ]\033[0m ");
    vprintf(format, args2);
    fflush(stdout);
}

void warning(const char *format, ...)
{
    va_list args1;
    va_list args2;

    #ifndef DEBUG
        return;
    #endif
    va_start(args1, format);
    va_copy(args2, args1);
    show_hour(stdout);
    printf(" \033[93m[ WARNING ]\033[0m ");
    vprintf(format, args2);
    fflush(stdout);
}

void error(const char *format, ...)
{
    va_list args1;
    va_list args2;

    #ifndef DEBUG
        return;
    #endif
    va_start(args1, format);
    va_copy(args2, args1);
    show_hour(stdout);
    printf(" \033[91m[  ERROR  ]\033[0m ");
    vprintf(format, args2);
    fflush(stdout);
}

void greeding(const char *format, ...)
{
    va_list args1;
    va_list args2;

    #ifndef DEBUG
        return;
    #endif
    va_start(args1, format);
    va_copy(args2, args1);
    show_hour(stdout);
    printf(" \033[92m[  GREAT  ]\033[0m ");
    vprintf(format, args2);
    fflush(stdout);
}
