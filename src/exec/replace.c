/*
** EPITECH PROJECT, 2019
** replace.h
** File description:
** replace
*/

#include "sh.h"
#include "vec.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char *replace_value(char *str, shell_t *shell)
{
    char *dest = xmalloc(strlen(str) + 1);
    int i = 0;

    for (i = 0; *str && *str != '$'; i += 1) {
        dest[i] = *str;
        str++;
    }
    dest[i] = '\0';
    str++;
    if (*str && (!strcmp(str, "?") || !strcmp(str, "status")))
        return (my_realloc(dest, int_to_str(shell->status)));
    if (*str && pars_env(str) != -1)
        return (my_realloc(dest, value_env(str)));
    for (int i = 0; *str && str[i]; i += 1)
        str[i] -= 32;
    if (*str && pars_env(str) != -1)
        return (my_realloc(dest, space_to_point(value_env(str))));
    return (NULL);
}

char *put_var(char *str, shell_t *shell, int *br)
{
    char *dest;

    if (value_echo(str)) {
        shell->status = 1;
        *br = 1;
        return (NULL);
    }
    dest = replace_value(str, shell);
    if (dest == NULL) {
        shell->status = 1;
        *br = 1;
        return (NULL);
    }
    return (dest);
}

vec_t *replace_var(vec_t *cmd, shell_t *shell)
{
    char *dest;
    vec_t *vec;
    char *separators[] = SEPARATOR;
    int br = 0;

    for (int i = 0; i < (int)cmd->element; i += 1) {
        for (int j = 0; !br && ((char *)cmd->content[i])[j]; j += 1)
            (((char *)cmd->content[i])[j] == '$' && ((char *)cmd->content[i])
            [j + 1]) ? cmd->content[i] =
            put_var((char *)cmd->content[i], shell, &br) : 0;
        if (br)
            return (NULL);
    }
    dest = my_realloc((char *) cmd->content[0], "");
    for (int i = 1; i < (int) cmd->element; i += 1) {
        dest = my_realloc(dest, " ");
        dest = my_realloc(dest, (char *) cmd->content[i]);
    }
    vec = my_str_to_word_tab_plus(dest, " \t\n", separators);
    free(dest);
    return (vec);
}

vec_t *replace_alias(vec_t *cmd, shell_t *shell)
{
    char *dest;
    vec_t *vec;
    char *separators[] = SEPARATOR;

    cmd = replace_var(cmd, shell);
    if (cmd == NULL)
        return (cmd);
    for (int j = 0; j < (int) shell->alias->element; j += 1)
        (!strcmp((char *)cmd->content[0], ((alias_t *)shell->alias->
        content[j])->alias)) ? cmd->content[0] =
        my_realloc(((alias_t *)shell->alias->content[j])->cmd, "") : 0;
    dest = my_realloc((char *) cmd->content[0], "");
    for (int i = 1; i < (int) cmd->element; i += 1) {
        dest = my_realloc(dest, " ");
        dest = my_realloc(dest, (char *) cmd->content[i]);
    }
    vec = my_str_to_word_tab_plus(dest, " \t\n", separators);
    free(dest);
    return (vec);
}
