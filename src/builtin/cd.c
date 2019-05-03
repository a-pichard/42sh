/*
** EPITECH PROJECT, 2019
** cd
** File description:
** cd
*/

#include "sh.h"
#include "vec.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

void check_dir(char *path, char *temp_prev)
{
    struct stat myfile;
    int ret = stat(path, &myfile);

    if (ret == -1) {
        my_puterr(path);
        my_puterr(": No such file or directory.\n");
    } else if (S_ISDIR(myfile.st_mode) == 0) {
        my_puterr(path);
        my_puterr(": Not a directory.\n");
    } else {
        my_puterr(path);
        my_puterr(": Permission denied.\n");
    }
    free(temp_prev);
}

int go_home(shell_t *shell)
{
    char *temp_prev = getcwd(NULL, 0);
    char *home = getenv("HOME");
    char *temp_now;

    if (chdir(home) == -1) {
        my_puterr("cd: No home directory.\n");
        free(temp_prev);
        return (1);
    }
    temp_now = getcwd(NULL, 0);
    setenv("PWD", temp_now, 1);
    free(temp_now);
    if (shell->prev_dir != NULL)
        free(shell->prev_dir);
    shell->prev_dir = temp_prev;
    return (1);
}

int my_cd(vec_t *params, shell_t *shell)
{
    if (params->element == 1) {
        shell->status = go_home(shell);
        return (shell->status);
    }
    else if (params->element > 2) {
        my_puterr("cd: Too many arguments.\n");
        shell->status = 1;
        return (shell->status);
    } else {
        shell->status = cd_with_args(params, shell);
        return (shell->status);
    }
}