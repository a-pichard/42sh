/*
** EPITECH PROJECT, 2019
** command
** File description:
** command
*/

#include "vec.h"
#include "sh.h"
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

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

void do_command(vec_t *command, UNUSED shell_t *shell)
{
    my_bin(command->content[0], command);
    execvp(command->content[0], (char * const *)command->content);
    my_exiterr(command->content[0], ": Command not found.\n", 1);
}

int command(vec_t *command, shell_t *shell, int files[2])
{
    char *builtin[] = COMMAND_STR;
    int (*func[])(vec_t *params, shell_t *status) = FUNCTION_PTR;
    int n = index_of_str((char *)(command->content[0]), builtin);
    int pid;

    if (n == 2 || n == 3 || n == 4 || (n == 1 &&
            (int)command->element > 1) || n == 6) {
        (func[n])(command, shell);
        return (-1);
    }
    pid = fork();
    if (pid == -1) {
        my_exiterr("", "fork error\n", 84);
    } else if (!pid) {
        dup2(files[0], 0);
        dup2(files[1], 1);
        ((n == -1)?(&do_command)(command, shell):(func[n])(command, shell));
        if (n != -1)
            exit(0);
    }
    return (pid);
}
