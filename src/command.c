/*
** EPITECH PROJECT, 2019
** command
** File description:
** command
*/

#include "vec.h"
#include "sh.h"

int command(vec_t *command, shell_t *shell)
{
    char *builtin[] = {"env", "setenv", "unsetenv", "exit", "cd", "echo", NULL};
    int (*function[])(vec_t *params, shell_t *status) = {my_env, my_setenv,
        my_unsetenv, my_exit, my_cd, my_echo, NULL};
    int n = index_of_str((char *)(command->content[0]), builtin);

    if (n != -1) {
        (function[n])(command, shell);
    } else {
        // try to execute a program
    }
}