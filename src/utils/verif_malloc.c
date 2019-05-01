/*
** EPITECH PROJECT, 2019
** verif_xmalloc
** File description:
** verrif xmalloc
*/

#include "sh.h"

void *xxmalloc(int size)
{
    void *ptr = malloc(size);
    char err_msg[] = "xmalloc failed !\n";

    if (ptr == NULL) {
        write(2, err_msg, strlen(err_msg));
        exit(84);
    }
    return (ptr);
}