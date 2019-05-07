/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** main
*/

#include "sh.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

void init_shell(shell_t *sh)
{
    sh->status = 0;
    sh->prev_dir = NULL;
}

int main(void)
{
    char *str = NULL;
    char *separators[] = SEPARATOR;
    size_t n = 0;
    shell_t shell;
    int r = 0;

    init_shell(&shell);
    while (42) {
        if (isatty(0) == 1)
            my_putstr("salut bg> ");
        if ((r = getline(&str, &n, stdin)) < 1) {
            my_putstr("exit\n");
            exit (shell.status);
        }
        if (strlen(str) < 2)
            continue;
        if (str[r - 1] == '\n') {
            str[r - 1] = '\0';
        }
        vec_t *vec = my_str_to_word_tab_plus(str, " \t", separators);
        command(vec, &shell);
    }
}
