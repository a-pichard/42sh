/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** my_strcat
*/

#include "sh.h"
#include <stdlib.h>
#include <string.h>

char *my_strcat(const char *src, const char *src_bis)
{
    int len;
    char *str;
    int i;
    int j;

    len = strlen(src) + strlen(src_bis);
    str = xmalloc(sizeof(char) * (len + 1));
    for (i = 0; src[i] != '\0'; i++)
        str[i] = src[i];
    for (j = 0; src_bis[j] != '\0'; j++)
        str[i + j] = src_bis[j];
    str[i + j] = '\0';
    return (str);
}

char *vec_to_str(vec_t *cmd, int n)
{
    char *dest = "";

    for (int i = 0; i < (int) cmd->element; i += 1) {
        dest = my_realloc(dest, (char *)cmd->content[i]);
        if (i + 1 < (int) cmd->element)
            dest = my_realloc(dest, " ");
    }
    dest = my_realloc(dest, "\n");
    if (n)
        write_history(dest);
    return (dest);
}
