/*
** EPITECH PROJECT, 2019
** pars_env.c
** File description:
** pars env
*/

#include "sh.h"
#include "vec.h"
#include <string.h>
#include <stdio.h>

int pars_env(char *str)
{
    int br = 0;
    extern char **environ;

    for (int i = 0; environ[i] != NULL; i += 1) {
        for (int j = 0; str[j] != '\0' && !br; j += 1)
            (environ[i][j] != '\0' && str[j] == environ[i][j])?0:(br = 1);
        if (!br)
            return (i);
        else
            br = 0;
    }
    return (-1);
}

char *value_env(char *str)
{
    extern char **environ;
    char *dest = strdup(environ[pars_env(str)]);

    for (int i = 0; str[i]; i += 1)
        dest++;
    dest++;
    return (dest);
}
