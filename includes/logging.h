/*
** EPITECH PROJECT, 2024
** Panoramix
** File description:
** logging
*/

#ifndef INCLUDED_LOGGING_H
    #define INCLUDED_LOGGING_H

    #include "headers.h"

void __attribute__((format(__printf__, 1, 2)))
debug(const char *format, ...);
void __attribute__((format(__printf__, 1, 2)))
info(const char *format, ...);
void __attribute__((format(__printf__, 1, 2)))
warning(const char *format, ...);
void __attribute__((format(__printf__, 1, 2)))
error(const char *format, ...);
void __attribute__((format(__printf__, 1, 2)))
greeding(const char *format, ...);

#endif
