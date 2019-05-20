/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** init
*/

#include "sh.h"
#include <stdio.h>

void init_shell(shell_t *shell)
{
    FILE *fd = fopen("./42shrc", "r");
    char *str = NULL;
    size_t n = 0;
    int r;

    if (fd == NULL)
        return;

    while (42) {
        if ((r = getline(&str, &n, fd)) < 1)
            return;
        exec_separator(str, shell);
        str = NULL;
        n = 0;
    }
}