/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** cd_with_args
*/

#include "sh.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

static int go_to_path(char *path, shell_t *shell)
{
    char *temp_prev = getcwd(NULL, 0);
    char *temp_now;

    if (chdir(path) == -1) {
        check_dir(path, temp_prev);
        return (1);
    } else {
        temp_now = getcwd(NULL, 0);
        setenv("PWD", temp_now, 1);
        free(temp_now);
        if (shell->prev_dir != NULL)
            free(shell->prev_dir);
        shell->prev_dir = temp_prev;
        return (0);
    }
}

static int go_back(shell_t *shell)
{
    char *temp = getcwd(NULL, 0);

    if (shell->prev_dir == NULL) {
        my_puterr(": No such file or directory.\n");
        free(temp);
        return (1);
    } else {
        chdir(shell->prev_dir);
        setenv("PWD", shell->prev_dir, 1);
        free(shell->prev_dir);
        shell->prev_dir = temp;
        return (0);
    }
}

static char *get_path_for_search_from_home(char *path)
{
    char *home = getenv("HOME");

    if (home != NULL)
        return (my_strcat(home, path));
    else
        return (NULL);
}

static int search_from_home(char *arg, shell_t *shell)
{
    char *path = get_path_for_search_from_home(&arg[1]);
    char *temp_prev = getcwd(NULL, 0);
    char *temp_now;

    if (path == NULL) {
        my_puterr("No $home variable set.\n");
        free(temp_prev);
        return (1);
    }
    if (chdir(path) == -1) {
        check_dir(path, temp_prev);
    } else {
        temp_now = getcwd(NULL, 0);
        setenv("PWD", temp_now, 1);
        free(temp_now);
        if (shell->prev_dir != NULL)
            free(shell->prev_dir);
        shell->prev_dir = temp_prev;
    }
    free(path);
    return (0);
}

int cd_with_args(vec_t *params, shell_t *shell)
{
    char *arg = (char *)params->content[1];
    int len = strlen(arg);

    if (len == 1) {
        if (arg[0] == '-')
            return (go_back(shell));
    }
    if (arg[0] == '~')
        return (search_from_home(arg, shell));
    return (go_to_path((char *)params->content[1], shell));
}
