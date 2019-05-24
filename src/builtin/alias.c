/*
** EPITECH PROJECT, 2019
** alias.c
** File description:
** alias
*/

#include "sh.h"
#include "vec.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char *my_realloc(char *str, char *src)
{
    int i;
    int j;
    int k;
    int m;
    char *dest;

    for (i = 0; str[i] != '\0'; i += 1);
    for (j = 0; src[j] != '\0'; j += 1);
    dest = malloc(sizeof(char) * (i + j + 1));
    (dest == NULL)?exit(84):0;
    for (k = 0; k < i; k += 1)
        dest[k] = str[k];
    for (m = 0; k + m < i + j; m += 1)
        dest[k + m] = src[m];
    dest[k + m] = '\0';
    return (dest);
}

int my_alias(vec_t *params, shell_t *shell)
{
    alias_t *alias;
    char *dest;
    int const stop = params->element;

    if (stop <= 2)
        return (shell->status = 0);
    if (!strcmp((char *) params->content[1], "alias")) {
        my_puterr("alias: Too dangerous to alias that.\n");
        return (shell->status = 1);
        }
    ((alias = malloc(sizeof(alias_t))) == NULL)?my_puterr("malloc error\n"):0;
    alias->alias = my_realloc((char *) params->content[1], "");
    dest = my_realloc((char *) params->content[2], "");
    for (int i = 3; i < stop && params->content[i] != NULL; i += 1) {
        dest = my_realloc(dest, " ");
        dest = my_realloc(dest, (char *) params->content[i]);
    }
    alias->cmd = dest;
    push(shell->alias, alias);
    return (shell->status = 0);
}
