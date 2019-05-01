/*
** EPITECH PROJECT, 2019
** env
** File description:
** env
*/

#include "sh.h"
#include "vec.h"

int my_env(vec_t *params, shell_t *shell)
{
    for (int i = 0; environ[i] != NULL; i++)
        printf("%s\n", environ[i]);
}