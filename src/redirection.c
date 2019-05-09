/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** redirection
*/

#include "sh.h"
#include "vec.h"
#include <stdbool.h>

bool is_command_valid(cmd_t *command)
{

}

void redirection(vec_t *command, shell_t *shell)
{
    cmd_t *cmd = parser(command);
    int for_next = 0;
    int files[2] = {0, 1};

    printf("salut je suis la\n");

    if (!is_command_valid(cmd))
        return;
    for (int i = 0; i < cmd->nb_cmd; i++) {
        int tmp_files[2];
        char *tmp = get(cmd->sep, i);
        if (!strcmp(tmp, "|")) {
            pipe(tmp_files);
            files[1] = tmp_files[1];
            for_next = files[0];
        }
    }
}