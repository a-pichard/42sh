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
    write(1, str, strlen(str));
}

void my_puterr(char const *str)
{
    write(2, str, strlen(str));
}

void my_putnbr(int n)
{
    if (n < 0) {
        my_putchar('-');
        n = -n;
        my_putnbr(n);
        return;
    }
    if (n <= 9) {
        my_putchar('0' + n);
    } else {
        my_putnbr(n / 10);
        my_putchar('0' + n % 10);
    }
}
