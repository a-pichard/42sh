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

bool is_command_valid(cmd_t *command)
{
    // (void) command;
    return true;
}

static void add_pid(vec_t *vec, int pid)
{
    int *new = malloc(sizeof(int));

    *new = pid;
    push(vec, new);
}

static bool update_file(cmd_t *cmd, int i, int files[2], int *for_next)
{
    int tmp_files[2];
    void *tmp = get(cmd->sep, i);

    if (tmp == NULL) {
        return true;
    } else if (!strcmp(tmp, "|")) {
        pipe(tmp_files);
        files[1] = tmp_files[1];
        *for_next = tmp_files[0];
        return true;
    } else if (is_redir(tmp)) {
        if (!strcmp(tmp, ">") || !strcmp(tmp, ">>"))
            files[1] = open(get(cmd->cmd[i + 1], 0), !strcmp(tmp, ">>")?
            O_WRONLY | O_CREAT | O_APPEND:O_WRONLY | O_TRUNC | O_CREAT, 0644);
        else
            files[0] = open(get(cmd->cmd[i + 1], 0), !strcmp(tmp, "<<")?
            O_RDONLY : O_RDONLY, 0644);    
        tmp = cmd->cmd[i + 1];
        cmd->cmd[i + 1] = cmd->cmd[i];
        cmd->cmd[i] = tmp;
        return false;
    } else {
        return true;
    }
    return false;
}

vec_t *redirection(vec_t *commands, shell_t *shell)
{
    cmd_t *cmd = parser(commands);
    vec_t *pid = create_vec();
    int for_next = 0;
    int files[2] = {0, 1};
    int return_pid;

    if (!is_command_valid(cmd))
        return NULL;
    for (int i = 0; i < (cmd->nb_cmd - 1); i++) {
        if (update_file(cmd, i, files, &for_next)) {
            return_pid = command(cmd->cmd[i], shell, files);
            add_pid(pid, return_pid);
            close_fd(files);
            files[0] = for_next;
            files[1] = 1;
        }
    }
    return (pid);
}