/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** my_shell
*/

#include "sh.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

static void exit_shell(shell_t *shell, char *cmd)
{
    int status = shell->status;

    my_putstr("exit\n");
    if (cmd != NULL)
        free(cmd);
    if (shell->prev_dir != NULL)
        free(shell->prev_dir);
    exit(status);
}

static void exec(char *str, shell_t *shell)
{
    vec_t *vec;
    char *separators[] = SEPARATOR;

    vec = my_str_to_word_tab_plus(str, " \t\n", separators);
    if (vec->element == 0) {
        free(str);
        destroy_vec(vec, free);
        return;
    }
    free(str);
    str = NULL;
    command(vec, shell);
    destroy_vec(vec, free);
}

void myshell(shell_t *shell)
{
    char *str = NULL;
    size_t n = 0;
    int r;

    while (42) {
        prompt();
        if ((r = getline(&str, &n, stdin)) < 1)
            exit_shell(shell, str);
        exec(str, shell);
        str = NULL;
    }
}
