/*
** EPITECH PROJECT, 2019
** echo
** File description:
** echo
*/

#include "sh.h"
#include "vec.h"
#include <string.h>
#include <unistd.h>

int char_instr(char *str, char c)
{
    for (int i = 0; str[i]; i += 1)
        if (str[i] == c)
            return (1);
    return (0);
}

char *space_to_point(char *str)
{
    for (int i = 0; str[i]; i += 1)
        if (str[i] == ':')
            str[i] = ' ';
    return (str);
}

int value_echo(char *str)
{
    char *mem = strdup(str);

    for (; *mem != '$'; mem++);
    mem++;
    if (!strcmp(mem, "?") || !strcmp(mem, "status"))
        return (0);
    if (pars_env(mem) != -1)
        return (0);
    for (int i = 0; mem[i]; i += 1)
        mem[i] -= 32;
    if (pars_env(mem) != -1)
        return (0);
    for (int i = 0; mem[i]; i += 1)
        mem[i] += 32;
    write(2, mem, strlen(mem));
    my_puterr(": Undefined variable.\n");
    return (1);
}

void print_value(char *str, shell_t *shell)
{
    for (; *str && *str != '$'; str++)
        my_putchar(*str);
    if (*str != '$')
        return;
    str++;
    if (*str && (!strcmp(str, "?") || !strcmp(str, "status"))) {
        my_putnbr(shell->status);
        return;
    }
    if (*str && pars_env(str) != -1) {
        my_putstr(value_env(str));
        return;
    }
    for (int i = 0; *str && str[i]; i += 1)
        str[i] -= 32;
    if (*str && pars_env(str) != -1) {
        my_putstr(space_to_point(value_env(str)));
        return;
    }
    my_putchar('$');
}

int my_echo(vec_t *params, shell_t *shell)
{
    int e;
    int status = 0;

    e = (params->element >= 2 && !strcmp((char *)params->content[1], "-n"))?1:0;
    for (int i = 1 + e; (int) params->element > i && !status; i += 1) {
        if (char_instr((char *)params->content[i], '$'))
            status = value_echo((char *)params->content[i]);
        else if (char_instr((char *)params->content[i], '?')) {
            my_puterr("echo: No match.\n");
            status = 1;
        }
    }
    if (status)
        return (shell->status = status);
    for (int i = 1 + e; (int) params->element > i && !status; i += 1) {
        print_value((char *)params->content[i], shell);
        (i + 1 < (int) params->element) ? write(1, " ", 1) : 0;
    }
    (!e && !status) ? write(1, "\n", 1) : 0;
    return (shell->status = status);
}
