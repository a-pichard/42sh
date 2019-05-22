/*
** EPITECH PROJECT, 2019
** my_atoi.c
** File description:
** my_atoi
*/

#include "sh.h"
#include <stdio.h>
#include <string.h>

long my_strtol(char *str, char **end)
{
    char *current = str;
    long n = 0;
    long signe = 0;

    if (*current == '-') {
        signe = 1;
        current = current + 1;
    }
    while (*current >= '0' && *current <= '9') {
        n = n * 10 + (*current - '0');
        current = current + 1;
    }
    *end = current;
    if (signe) {
        n = -n;
    }
    return (n);
}

int my_atoi(char *str)
{
    char *end;
    long a = my_strtol(str, &end);

    if (*end != '\0') {
        return (-666);
    }
    return ((int) a);
}

int my_atoi_f(char *str, int n)
{
    char *end;
    long a;
    char *mem = xmalloc(strlen(str) + 1);
    int i;

    for (i = 0; str[i] != '\0'; i += 1)
        mem[i] = str[i];
    mem[i] = '\0';
    for (int i = 0; i < n; i += 1)
        mem++;
    a = my_strtol(mem, &end);
    if (*end != '\0' || !a) {
        return (-666);
    }
    return ((int) a);
}

int my_atoi_d(char *str)
{
    char *end;
    long a;

    for (int i = 0; str[i] > '9' || str[i] < '0'; i += 1)
        str++;
    str++;
    a = my_strtol(str, &end);
    return ((int) a);
}
