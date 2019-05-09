/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** print_cmd
*/

#include "sh.h"

void print_cmd(cmd_t *cmd)
{
    int i = 0;
    int j = 0;

    while (i != cmd->nb_cmd) {
        if (cmd->cmd[i] == NULL) {
            i++;
            continue;
        }
        while (j != cmd->cmd[i]->element) {
            my_putstr(cmd->cmd[i]->content[j]);
            my_putchar('\n');
            j++;
        }
        j = 0;
        my_putchar('\n');
        if (i < cmd->sep->element) {
            my_putstr((char *)cmd->sep->content[i]);
            my_putstr("\n\n");
        }
        i++;
    }
}