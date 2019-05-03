/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** my_strcat
*/

#include "sh.h"
#include <stdlib.h>
#include <string.h>

char *my_strcat(char *src, char *src_bis)
{
    int len;
    char *str;
    int i;
    int j;

    if (src == NULL)
        return (src_bis);
    len = strlen(src) + strlen(src_bis);
    str = xmalloc(sizeof(char) * (len + 1));
    for (i = 0; src[i] != '\0'; i++)
        str[i] = src[i];
    for (j = 0; src_bis[j] != '\0'; j++)
        str[i + j] = src_bis[j];
    str[i + j] = '\0';
    return (str);
}