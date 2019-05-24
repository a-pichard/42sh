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

void put_alias(char *str, vec_t *alias)
{
    for (int i = 0; i < (int) alias->element; i += 1) {
        if (!strcmp(((alias_t *) alias->content[i])->alias, str)) {
            my_putstr(((alias_t *) alias->content[i])->cmd);
            my_putchar('\n');
        }
    }
}

void print_alias(vec_t *params, shell_t *shell)
{
    if (params->element == 2) {
        put_alias((char *)params->content[1], shell->alias);
        return;
    }
    for (int i = 0; i < (int) shell->alias->element; i += 1) {
        my_putstr(((alias_t *)shell->alias->content[i])->alias);
        for (int j = 0; j < 7 - (int)
                strlen(((alias_t *)shell->alias->content[i])->alias); j += 1)
            my_putchar(' ');
        my_putchar(' ');
        my_putstr(((alias_t *)shell->alias->content[i])->cmd);
        my_putchar('\n');
    }
}

int my_alias(vec_t *params, shell_t *shell)
{
    alias_t *alias;
    char *dest;
    int const stop = params->element;

    if (stop <= 2) {
        return (shell->status = 0);
    } else if (!strcmp((char *) params->content[1], "alias")) {
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
