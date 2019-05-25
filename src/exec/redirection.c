/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** redirection
*/

#include "sh.h"
#include "vec.h"
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

bool is_command_valid(const cmd_t *command)
{
    int in = 0;
    int out = 0;

    for (int i = 0; command->sep->content[i] != NULL; i += 1) {
        if (((char *)command->sep->content[i])[0] != '>' &&
            ((char *)command->sep->content[i])[0] != '<') {
            in = 0;
            out = 0;
        }
        (((char *)command->sep->content[i])[0] == '>') ? out += 1 : 0;
        (((char *)command->sep->content[i])[0] == '>') ? in = 0 : 0;
        (((char *)command->sep->content[i])[0] == '<') ? in += 1 : 0;
        (((char *)command->sep->content[i])[0] == '<') ? out = 0 : 0;
        (in >= 2) ? my_puterr("Ambiguous input redirect.\n") : 0;
        (out >= 2) ? my_puterr("Ambiguous output redirect.\n") : 0;
        (!command->cmd[i + 1]) ? my_puterr("Missing name for redirect.\n"): 0;
        (!command->cmd[i]) ? my_puterr("Invalid null command.\n"): 0;
        if (out >= 2 || in >= 2 || !command->cmd[i + 1] || !command->cmd[i])
            return (false);
    }
    return (true);
}

static void add_pid(vec_t *vec, int pid)
{
    int *new = malloc(sizeof(int));

    *new = pid;
    push(vec, new);
}

static void cmd_destoy(cmd_t *cmd)
{
    if (cmd != NULL) {
        destroy_vec(cmd->sep, free);
        for (int i = 0; i < cmd->nb_cmd; i++) {
            destroy_vec(cmd->cmd[i], free);
        }
        free(cmd->cmd);
        free(cmd);
    }
}

vec_t *redirection(vec_t *commands, shell_t *shell)
{
    cmd_t *cmd = parser(commands);
    vec_t *pid = create_vec();
    int for_next = 0;
    int files[2] = {0, 1};
    int return_pid;
    vec_t *mem;

    if (!is_command_valid(cmd))
        return NULL;
    for (int i = 0; i < (cmd->nb_cmd - 1); i++) {
        if (update_file(cmd, i, files, &for_next)) {
            mem = replace_alias(cmd->cmd[i], shell);
            (mem != NULL) ? return_pid = command(mem, shell, files) : 0;
            add_pid(pid, return_pid);
            close_fd(files);
            files[0] = for_next;
            files[1] = 1;
        }
    }
    cmd_destoy(cmd);
    return (pid);
}
