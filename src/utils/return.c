/*
** EPITECH PROJECT, 2019
** return.c
** File description:
** return
*/

#include "sh.h"

int puterr_nb(int nb, char *err, int ret)
{
    my_putnbr(nb);
    my_putstr(err);
    return (ret);
}

int puterr_str(char *str, char *err, int ret)
{
    my_putstr(str);
    my_putstr(err);
    return (ret);
}
