/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** tab_utils
*/

#include "sh.h"
#include <stdlib.h>
#include <string.h>

int get_tab_len(char **tab)
{
    int i = 0;

    while (tab[i] != NULL) {
        i++;
    }
    return (i);
}

void print_tab(char **wordtab)
{
    int i = 0;

    while (wordtab[i] != NULL) {
        my_putstr(wordtab[i]);
        my_putchar('\n');
        i++;
    }
}

void destroy_tab(char **wordtab)
{
    int i = 0;

    if (wordtab == NULL)
        return;
    while (wordtab[i] != NULL) {
        free(wordtab[i]);
        i++;
    }
    free(wordtab);
}

char **tabdup(char **env)
{
    char **copy = xmalloc(sizeof(char *) * (get_tab_len(env) + 1));
    int i = 0;

    while (env[i] != NULL) {
        if ((copy[i] = strdup(env[i])) == NULL) {
            my_puterr("malloc error.\n");
            exit(84);
        }
        i++;
    }
    copy[i] = NULL;
    return (copy);
}