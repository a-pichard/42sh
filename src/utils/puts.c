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
}

void my_putnbr(int n)
{
    long k = n;
    long i;

    if (k < 0) {
        my_putchar('-');
        k = -k;
    }
    if (k > 9) {
        my_putnbr(k / 10);
        i = k % 10;
        my_putchar(i + 48);
    } else {
        my_putchar(k + 48);
    }
}
