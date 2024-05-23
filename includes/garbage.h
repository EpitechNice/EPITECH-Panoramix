/*
** EPITECH PROJECT, 2024
** Panoramix
** File description:
** garbage
*/

#ifndef INCLUDED_GARBAGE_H
    #define INCLUDED_GARBAGE_H

    #include "headers.h"

/**
  * A simple linked list that contain all the necessary to store infos about
  * allocated chunks
  *
  * @tip
  * It is not recomended to manually use this struct, as it is only used to
  * store chunks of data, and even tho it takes more binary space, it is
  * better to split garbage collector and linked list.
*/
typedef struct _garbage_list {
    struct _garbage_list *prev;
    void *ptr;
    struct _garbage_list *next;
} _garbage_t;

typedef _garbage_t *garbage_t;

/**
  * @brief Allocate a chunck of memory, and save it into the trash bin
  *
  * @param size The size of the allocated chunk.
  *
  * @warning
  * The size parameter is the size of the RETURNED data chunck.
  * The garbage collector WILL allocate more data, in order to work.
  * This is an information you need to remember in case you are working on a
  * ressources-limited environement.
  *
  * @return The newly allocated piece of memory
*/
void *f_malloc(size_t size);

/**
  * @brief Free a chunck of memory ALLOCATED WITH f_malloc
  *
  * @param ptr Pointer to the chunck to free.
  *
  * @note
  * This function is secure. With it, you can not :
  * - use after free
  * - double free
  * - memory leak
  * Please not however that it is incredibly more time consuming than a regular
  * free.
*/
void f_free(void *ptr);

void f_free_ref(void *ptr);
void f_cleanup(void);

    #define FREE __attribute__((cleanup(f_free_ref)))

#endif
