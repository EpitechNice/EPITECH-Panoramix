/*
** EPITECH PROJECT, 2024
** C-Project-Template
** File description:
** smart_pointers
*/

#include "smart_pointers.h"

smart_ptr_t dev_make_ptr(size_t size)
{
    __attribute__((cleanup(dev_smart_ptr_cleanup))) smart_ptr_t p =
        (smart_ptr_t)f_malloc(sizeof(_smart_ptr_t));
    p->size = size;
    p->data = f_malloc(size);
    p->__counter = 1;
    return share_ptr(p);
}

smart_ptr_t share_ptr(smart_ptr_t p)
{
    p->__counter += 1;
    return p;
}

void dev_smart_ptr_cleanup(void *variable_pointer)
{
    smart_ptr_t v = *(smart_ptr_t *)variable_pointer;

    v->__counter -= 1;
    if (v->__counter == 0 && v->data)
        f_free(v->data);
    if (v->__counter == 0)
        f_free(v);
}