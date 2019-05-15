/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** is_redir
*/

#include <string.h>
#include <stdbool.h>

bool is_redir(const char *str)
{
    int len;

    if (str == NULL)
        return (false);
    len = strlen(str);
    if (len != 1 && len != 2)
        return (false);
    if (!strcmp(str, ">"))
        return (true);
    if (!strcmp(str, ">>"))
        return (true);
    if (!strcmp(str, "<"))
        return (true);
    if (!strcmp(str, "<<"))
        return (true);
    return (false);
}

int is_redirs(char *str)
{
    int len;

    if (str == NULL)
        return (0);
    len = strlen(str);
    if (len != 1 && len != 2)
        return (0);
    if (!strcmp(str, ">"))
        return (1);
    if (!strcmp(str, ">>"))
        return (1);
    if (!strcmp(str, "<"))
        return (1);
    if (!strcmp(str, "<<"))
        return (1);
    if (!strcmp(str, "|"))
        return (1);
    return (0);
}