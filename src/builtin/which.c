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

int is_an_alias(vec_t *params, shell_t *shell, int j)
{
    int pass = 0;

    for (int i = 0; shell->alias->content[i] != NULL; i++) {
        if (!strcmp(params->content[j], \
        ((alias_t *)shell->alias->content[i])->alias)) {
            my_putstr(params->content[j]);
            my_putstr(":   aliased to ");
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

int is_an_builtin(vec_t *params, UNUSED shell_t *shell, int j)
{
    char *builtin[] = {"env", "setenv", "unsetenv", "exit", "cd", "echo", \
    "alias", "which", NULL};

    for (int i = 0; builtin[i] != NULL; i++)
        if (!strcmp(params->content[j], builtin[i])) {
            my_putstr(params->content[j]);
            my_putstr(": shell built-in command.\n");
            return (1);
        }
    return (0);
}

int my_which(vec_t *params, shell_t *shell)
{
    int pass = 0;

    if (params->element == 1) {
        my_puterr(params->content[0]);
        my_puterr(": Too few arguments.\n");
        return (1);
    }
    for (int j = 1; params->content[j] != NULL; pass = 0, j++) {
        pass = is_an_alias(params, shell, j);
        if (pass != 1)
            pass = is_an_builtin(params, shell, j);
        if (pass == 0) {
            my_puterr(params->content[j]);
            my_puterr(": Command not found.\n");
        }
    }
    return (0);
}