/*
** EPITECH PROJECT, 2019
** Error
** File description:
** error message
*/

#include "sh.h"
#include <stdlib.h>

void my_exiterr(char *str, char *err, int n)
{
    my_puterr(str);
    my_puterr(err);
    exit(n);
}