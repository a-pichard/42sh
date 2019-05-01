/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** main
*/

#include "sh.h"
#include <stdio.h>

int main(void)
{
    char *str = NULL;
    char *separators[] = SEPARATOR;
    size_t n = 0;
    shell_t shell = {0};

    while (42) {
        int r = getline(&str, &n, stdin);
        if (str[r - 1] == '\n') {
            str[r - 1] = '\0';
        }
        vec_t *vec = my_str_to_word_tab_plus(str, " \t", separators);
        command(vec, &shell);
    }
}