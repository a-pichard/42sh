/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** puts
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void my_putchar(char c)
{
    write(1, &c, 1);
}

void my_putstr(char const *str)
{
    int i = 0;

    while (str[i] != '\0') {
        my_putchar(str[i]);
        i++;
    }
}

void my_puterr(char const *str)
{
    write(2, str, strlen(str));
    exit (84);
}