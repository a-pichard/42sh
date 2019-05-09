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
    return true;
}

void redirection(vec_t *commands, shell_t *shell)
{
    cmd_t *cmd = parser(commands);
    vec_t *pid = create_vec();
    int for_next = 0;
    int files[2] = {0, 1};
    int return_pid;

    print_cmd(cmd);
    printf("salut je suis la\n");

    if (!is_command_valid(cmd))
        return;
    for (int i = 0; i < (cmd->nb_cmd - 1); i++) {
        int tmp_files[2];
        if (files[0] != 0)
            close(files[0]);
        if (files[1] != 1)
            close(files[1]);
        files[0] = for_next;
        files[1] = 1;
        char *tmp = get(cmd->sep, i);
        if (tmp == NULL) {
            return_pid = command(cmd->cmd[i], shell, files);
        } else if (!strcmp(tmp, "|")) {
            pipe(tmp_files);
            files[1] = tmp_files[1];
            for_next = tmp_files[0];
            return_pid = command(cmd->cmd[i], shell, files);
        } else {
            return_pid = command(cmd->cmd[i], shell, files);
        }
        int *new = malloc(sizeof(int));
        *new = return_pid;
        push(pid, new);
    }
    for (int i = 0; i < pid->element; i++) {
        int s = 0;
        waitpid(*(int *)(pid->content[i]), &s, 0);
        (WIFSIGNALED(s))?print_err(s, shell):(shell->status = WEXITSTATUS(s));
    }
}