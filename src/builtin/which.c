/*
** EPITECH PROJECT, 2019
** wich
** File description:
** wich bultin
*/

#include "vec.h"
#include "sh.h"
#include "stdio.h"
#include "string.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int is_an_alias(vec_t *params, shell_t *shell, int j, int option)
{
    int pass = 0;

    for (int i = 0; shell->alias->content[i] != NULL; i++) {
        if (!strcmp(params->content[j], \
        ((alias_t *)shell->alias->content[i])->alias)) {
            my_putstr(params->content[j]);
            my_putstr((option == 0) ? ":   aliased to " : " is aliased to ");
            my_putstr(((alias_t *)shell->alias->content[i])->cmd);
            my_putchar('\n');
            pass = 1;
            break;
        }
    }
    if (pass == 1)
        return (1);
    return (0);
}

int is_an_builtin(vec_t *params, int j, int option)
{
    char *builtin[] = {"env", "setenv", "unsetenv", "exit", "cd", "echo", \
    "alias", "which", "where", NULL};

    for (int i = 0; builtin[i] != NULL; i++)
        if (!strcmp(params->content[j], builtin[i])) {
            my_putstr(params->content[j]);
            my_putstr((option == 0) ? ": shell built-in command." : \
            " is a shell built-in");
            my_putchar('\n');
            return (1);
        }
    return (0);
}

int is_an_path(vec_t *params, int j, int option)
{
    char *path = value_env("PATH=");
    char *separators[] = {NULL};
    vec_t *ptab = my_str_to_word_tab_plus(path, ":", separators);
    char *new_path = NULL;
    int pass = 0;
    int pass_where = 0;

    for (int i = 0; ptab->content[i] != NULL; i++) {
        new_path = strcat(strcat(ptab->content[i], "/"), params->content[j]);
        if (access(new_path, X_OK) == 0) {
            my_putstr(new_path);
            my_putchar('\n');
            pass = 1;
            pass_where = 1;
        }
        if (pass == 1 && option == 0)
            return (1);
        pass = 0;
    }
    destroy_vec(ptab, free);
    return ((option == 1) ? pass_where : 0);
}

int my_which(vec_t *params, shell_t *shell)
{
    int pass = 0;

    shell->status = (params->element == 1)?1:0;
    if (params->element == 1) {
        my_puterr(params->content[0]);
        my_puterr(": Too few arguments.\n");
        return (1);
    }
    for (int j = 1; params->content[j] != NULL; pass = 0, j++) {
        pass = is_an_alias(params, shell, j, 0);
        if (pass != 1)
            pass = is_an_builtin(params, j, 0);
        if (pass != 1)
            pass = is_an_path(params, j, 0);
        if (pass == 0) {
            my_puterr(params->content[j]);
            my_puterr(": Command not found.\n");
            shell->status = 1;
        }
    }
    return (0);
}

int my_where(vec_t *params, shell_t *shell)
{
    int pass = 0;

    shell->status = 0;
    if (params->element == 1) {
        my_puterr(params->content[0]);
        my_puterr(": Too few arguments.\n");
        shell->status = 1;
        return (1);
    }
    for (int j = 1; params->content[j] != NULL; pass = 0, j++) {
        pass += is_an_alias(params, shell, j, 1);
        pass += is_an_builtin(params, j, 1);
        pass += is_an_path(params, j, 1);
        if (pass == 0) {
            shell->status = 1;
        }
    }
    return (0);
}