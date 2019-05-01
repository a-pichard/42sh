/*
** EPITECH PROJECT, 2019
** index_of
** File description:
** index_of
*/

#include <stddef.h>
#include <string.h>

int index_of(char c, char *tab)
{
    for (int i = 0; tab[i] != '\0'; i++) {
        if (tab[i] == c) {
            return (i);
        }
    }
    return (-1);
}

int index_of_str(char *str, char **tab)
{
    for (int i = 0; tab[i] != NULL; i++) {
        if (strcmp(str, tab[i]) == 0) {
            return (i);
        }
    }
    return (-1);
}