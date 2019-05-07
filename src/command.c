/*
** EPITECH PROJECT, 2019
** command
** File description:
** command
*/

#include "vec.h"
#include "sh.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int command(vec_t *command, shell_t *shell)
{
    char *builtin[] = {"env", "setenv", "unsetenv", "exit", "cd", "echo", NULL};
    int (*function[])(vec_t *params, shell_t *status) = {my_env, my_setenv,
        my_unsetenv, my_exit, my_cd, my_echo, NULL};
    int n = index_of_str((char *)(command->content[0]), builtin);
    int pid = 0;

    if (n != -1) {
        (function[n])(command, shell);
    } else {
        pid = fork();
        if (pid == -1) {
            my_puterr("fork error\n");
            return (-1);
        } else if (!pid) {
            execvp(command->content[0], (char * const *)command->content);
            my_puterr("execvp a fail\n");
            exit(84);
        } else {
            return (pid);
        }
    }
    return (0);
}
