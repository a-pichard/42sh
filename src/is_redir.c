/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** is_redir
*/

#include <string.h>

int is_redir(char *str)
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
    return (0);
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