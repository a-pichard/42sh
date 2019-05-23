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

vec_t *replace_alias(vec_t *cmd, shell_t *shell)
{
    char *dest;
    vec_t *vec;
    char *separators[] = SEPARATOR;

    for (int j = 0; j < (int) shell->alias->element; j += 1)
        (!strcmp((char *)cmd->content[0], ((alias_t *)shell->alias->
        content[j])->alias)) ? cmd->content[0] =
        my_realloc(((alias_t *)shell->alias->content[j])->cmd, "") : 0;
    dest = my_realloc((char *) cmd->content[0], "");
    for (int i = 1; i < (int) cmd->element; i += 1) {
        dest = my_realloc(dest, " ");
        dest = my_realloc(dest, (char *) cmd->content[i]);
    }
    vec = my_str_to_word_tab_plus(dest, " \t\n", separators);
    free(dest);
    return (vec);
}

int my_alias(vec_t *params, shell_t *shell)
{
    alias_t *alias;
    char *dest;

    if (params->element <= 2)
        return (shell->status = 0);
    if (!strcmp((char *) params->content[1], "alias")) {
        my_puterr("alias: Too dangerous to alias that.\n");
        return (shell->status = 1);
        }
    ((alias = malloc(sizeof(alias_t))) == NULL)?my_puterr("malloc error\n"):0;
    alias->alias = my_realloc((char *) params->content[1], "");
    dest = my_realloc((char *) params->content[2], "");
    for (int i = 3; i < (int) params->element; i += 1) {
        dest = my_realloc(dest, " ");
        dest = my_realloc(dest, (char *) params->content[i]);
    }
    alias->cmd = dest;
    push(shell->alias, alias);
    return (shell->status = 0);
}
