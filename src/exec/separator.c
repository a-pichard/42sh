/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** separator
*/

#include "sh.h"
#include <string.h>
#include <stdlib.h>

static bool or(shell_t *shell)
{
    if (shell->status == 0) {
        return (false);
    }
    return (true);
}

static bool and(shell_t *shell)
{
    if (shell->status == 0) {
        return (true);
    }
    return (false);
}

static bool semicolon(shell_t *shell)
{
    (void) shell;
    return (true);
}

static void check_exec(vec_t *command, shell_t *shell, size_t *i,
        bool (*ptr)(shell_t *shell))
{
    if (ptr(shell)) {
        exec(command->content[*i], shell);
    } else {
        while (*i < command->element && strcmp(command->content[*i], ";")) {
            free(command->content[*i]);
            *i = *i + 1;
        }
    }
}

void exec_separator(char *str, shell_t *shell)
{
    char *sep[] = {"||", "&&", ";", NULL};
    bool (*functions[])(shell_t *shell) = {or, and, semicolon, NULL};
    vec_t *command = parser_sep(str);
    int index = -1;
    bool (*ptr)(shell_t *shell) = semicolon;

    for (size_t i = 0; i < command->element; i++) {
        index = index_of_str(command->content[i], sep);
        if (index == -1) {
            check_exec(command, shell, &i, ptr);
        } else {
            free(command->content[i]);
            ptr = functions[index];
        }
    }
    destroy_vec(command, NULL);
}