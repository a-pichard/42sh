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

    (isatty(0) == 1) ? my_putstr("exit\n") : 0;
    if (cmd != NULL)
        free(cmd);
    if (shell->prev_dir != NULL)
        free(shell->prev_dir);
    exit(status);
}

static void parse_pid(vec_t *pid, shell_t *shell)
{
    int s;

    if (pid == NULL)
        shell->status = 1;
    for (int i = 0; pid != NULL && i < (int) pid->element; i++) {
        s = 0;
        if (*(int *)(pid->content[i]) != -1) {
            waitpid(*(int *)(pid->content[i]), &s, 0);
            (WIFSIGNALED(s))?print_err(s, shell):
                (shell->status = WEXITSTATUS(s));
        }
    }
}

void exec(char *str, shell_t *shell)
{
    char *separators[] = SEPARATOR;
    vec_t *vec = my_str_to_word_tab_plus(str, " \t\n", separators);
    vec_t *pid;

    if (vec->element == 0) {
        free(str);
        destroy_vec(vec, free);
        return;
    }
    free(str);
    pid = redirection(vec, shell);
    parse_pid(pid, shell);
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
        if (strlen(str) < 2) {
            free(str);
            str = NULL;
            continue;
        }
        if (BONUS)
            str = history(str);
        (str != NULL) ? exec_separator(str, shell) : 0;
        str = NULL;
        n = 0;
    }
}
