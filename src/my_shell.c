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

void exec(char *str, shell_t *shell)
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
    vec_t *pid = redirection(vec, shell);
    for (int i = 0; pid != NULL && i < pid->element; i++) {
        int s = 0;
        waitpid(*(int *)(pid->content[i]), &s, 0);
        (WIFSIGNALED(s))?print_err(s, shell):
            (shell->status = WEXITSTATUS(s));
    }
    destroy_vec(pid, free);
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
        exec_separator(str, shell);
        str = NULL;
    }
}
