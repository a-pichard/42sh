/*
** EPITECH PROJECT, 2019
** env
** File description:
** env
*/

#include "sh.h"
#include "vec.h"
#include <string.h>
#include <unistd.h>

int my_env(vec_t *info, shell_t *shell)
{
    for (int i = 0; environ[i] != NULL; i++) {
        write(1, environ[i], strlen(environ[i]));
        write(1, "\n", 1);
    }
}