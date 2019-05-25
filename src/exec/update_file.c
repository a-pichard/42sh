/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** update_file
*/

#include "sh.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

static void write_into_file(void *tmp, int files[2], cmd_t *cmd, int i)
{
    int flags = O_WRONLY | O_CREAT;

    if (!strcmp(tmp, ">") || !strcmp(tmp, ">>")) {
        flags |= (!strcmp(tmp, ">>")) ? O_APPEND : O_TRUNC;
        files[1] = open(get(cmd->cmd[i + 1], 0), flags, 0664);
    } else {
        files[0] = open(get(cmd->cmd[i + 1], 0), O_RDONLY, 0644);
        if (!strcmp(tmp, "<<"))
            redirect_stdin_double(tmp, files, cmd->cmd[i + 1]);
    }
    tmp = cmd->cmd[i + 1];
    cmd->cmd[i + 1] = cmd->cmd[i];
    cmd->cmd[i] = tmp;
}

bool update_file(cmd_t *cmd, int i, int files[2], int *for_next)
{
    int tmp_files[2];
    void *tmp = get(cmd->sep, i);

    if (tmp != NULL && !strcmp(tmp, "|")) {
        pipe(tmp_files);
        files[1] = tmp_files[1];
        *for_next = tmp_files[0];
    } else if (tmp != NULL && is_redir(tmp)) {
        write_into_file(tmp, files, cmd, i);
        return (false);
    }
    return (true);
}