/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** main
*/

#include "sh.h"
#include <stdio.h>
#include <unistd.h>

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

    init_shell(&shell);
    while (42) {
        if (isatty(0) == 1)
            my_putstr("salut bg> ");
        int r = getline(&str, &n, stdin);
        if (str[r - 1] == '\n') {
            str[r - 1] = '\0';
        }
        vec_t *vec = my_str_to_word_tab_plus(str, " \t", separators);
        int pid = command(vec, &shell);
        waitpid(pid, &shell.status, 0);
    }
}