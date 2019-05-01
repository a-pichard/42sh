/*
** EPITECH PROJECT, 2019
** echo
** File description:
** echo
*/

#include "sh.h"
#include "vec.h"
#include <string.h>

int char_instr(char *str, char c)
{
    for (int i = 0; str[i]; i += 1)
        if (str[i] == c)
            return (1);
    return (0);
}

int value_echo(char *str)
{
    char *mem = xmalloc(my_strlen(str));

    mem = strcpy(mem, str);
    for (int i = 0; mem[i] != '$'; i += 1)
        mem++;
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
    write(2, mem, my_strlen(mem));
    my_puterr(": Undefined variable.\n");
    return (1);
}

void print_value(char *str, shell_t *shell)
{
    for (int i = 0; mem[i] != '$'; i += 1) {
        write(1, mem[i], 1);
        mem++;
    }
    mem++;
    if (!strcmp(mem, "?") || !strcmp(mem, "status")) {
        my_putnbr(shell->status);
        return;
    }
    if (pars_env(mem) != -1) {
        write(value_env(str));
        return;
    }
    for (int i = 0; mem[i]; i += 1)
        mem[i] -= 32;
    if (pars_env(mem) != -1) {
        write(value_env(str));
        return;
    }
    write(1, str, my_strlen(str);
}

int my_echo(vec_t *params, shell_t *shell)
{
    int e;
    int status = 0;

    e = (param->element >= 2 && !strcmp((char *)params->content[1], "-n"))?1:0;
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
    if (int i = 1 + e; (int) params->element > i && !status; i += 1) {
        print_value((char *)params->content[i], shell);
        (i + 1 < (int) params->element) ? write(1, " ", 1) : 0;
    }
    (e && !status) ? write(1, "\n", 1) : 0;
    return (shell->status = status);
}
