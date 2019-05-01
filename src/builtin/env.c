/*
** EPITECH PROJECT, 2019
** env
** File description:
** env
*/

#include "sh.h"
#include "vec.h"

int my_env()
{
    for (int i = 0; environ[i] != NULL; i++) {
        write(1, environ[i], strlen(environ[i]));
        write(1, "\n", 1);
    }
}