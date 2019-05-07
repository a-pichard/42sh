/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** prompt
*/

#include "sh.h"
#include <unistd.h>

void prompt(void)
{
    if (isatty(0) == 1) {
        my_putstr(getlogin());
        my_putstr("@localhost");
        my_putstr("> ");
    }
}