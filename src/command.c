/*
** EPITECH PROJECT, 2019
** command
** File description:
** command
*/

#include "vec.h"
#include "sh.h"
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

int is_dir(char *file)
{
    struct stat fs;
    char dir;
    char *type = "pcdb-ls";

    if (lstat(file, &fs) == -1)
        return (-1);
    dir = type[(fs.st_mode & S_IFMT) >> 13];
    if (dir == 'd')
        return (0);
    if (dir == 'l')
        return (0);
    return (1);
}

void my_exiterr(char *str, char *err, int n)
{
    my_puterr(str);
    my_puterr(err);
    exit(n);
}

void my_bin(char *com, vec_t *command)
{
    extern char **environ;

    if (!is_dir(com) || (access(com, X_OK) == -1 && is_dir(com) != -1))
        my_exiterr(com, ": Permission denied.\n", 1);
    if (access(com, X_OK) != -1 &&
        execve(com, (char **)command->content, environ) == -1)
        my_exiterr(com, ": Exec format error. Wrong Architecture.\n", 126);
}

void print_err(int s, shell_t *shell)
{
    if (WTERMSIG(s) + 128 != 136)
        my_puterr(strsignal(WTERMSIG(s)));
    else
        my_puterr("Floating exception");
    if (WCOREDUMP(s))
        my_puterr(" (core dumped)\n");
    else
        my_puterr("\n");
    shell->status = WTERMSIG(s) + 128;
}

int command(vec_t *command, shell_t *shell)
{
    char *builtin[] = {"env", "setenv", "unsetenv", "exit", "cd", "echo", NULL};
    int (*function[])(vec_t *params, shell_t *status) = {my_env, my_setenv,
        my_unsetenv, my_exit, my_cd, my_echo, NULL};
    int n = index_of_str((char *)(command->content[0]), builtin);
    int pid = 0;
    int s;

    if (n != -1) {
        (function[n])(command, shell);
    } else {
        pid = fork();
        if (pid == -1) {
            my_puterr("fork error\n");
            return (-1);
        } else if (!pid) {
            my_bin(command->content[0], command);
            execvp(command->content[0], (char * const *)command->content);
            my_exiterr(command->content[0], ": Command not found\n", 1);
        }
        waitpid(pid, &s, 0);
        (WIFSIGNALED(s))?print_err(s, shell):(shell->status = WEXITSTATUS(s));
    }
    return (0);
}
