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
        (command->cmd[i + 1] == NULL) ? my_puterr("Missing name for redirect.\n"): 0;
        if (out >= 2 || in >= 2 || command->cmd[i + 1] == NULL)
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

static void get_user_stdin_input(int fd[2], UNUSED char *arg)
{
    char *str = NULL;
    size_t n = 0;

    my_putstr("? ");
    while (42) {
        if (getline(&str, &n, stdin) < 1 || str == NULL)
            break;
        my_putstr("? ");
        if (write(fd[1], str, strlen(str)) == -1)
            perror("write");
    }
}

static int redirect_stdin_double(void *tmp, int files[2])
{
    if (pipe(files) == -1)
        perror("pipe");
    get_user_stdin_input(files, tmp);
    dup2(files[0], 0);
    close(files[1]);
    return (1);
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

static bool update_file(cmd_t *cmd, int i, int files[2], int *for_next)
{
    int tmp_files[2];
    void *tmp = get(cmd->sep, i);

    if (tmp != NULL && !strcmp(tmp, "|")) {
        pipe(tmp_files);
        files[1] = tmp_files[1];
        *for_next = tmp_files[0];
    } else if (tmp != NULL && is_redir(tmp)) {
        if (!strcmp(tmp, ">") || !strcmp(tmp, ">>"))
            files[1] = open(get(cmd->cmd[i + 1], 0), !strcmp(tmp, ">>")?
            O_WRONLY | O_CREAT | O_APPEND:O_WRONLY | O_TRUNC | O_CREAT, 0664);
        else {
            files[0] = open(get(cmd->cmd[i + 1], 0), !strcmp(tmp, "<<")?
            O_RDONLY : O_RDONLY, 0644);
            (!strcmp(tmp, "<<")) ? redirect_stdin_double(tmp, files) : 0;
        }
        tmp = cmd->cmd[i + 1];
        cmd->cmd[i + 1] = cmd->cmd[i];
        cmd->cmd[i] = tmp;
        return (false);
    }
    return (true);
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
            return_pid = command(replace_alias(cmd->cmd[i], shell), shell, files);
            add_pid(pid, return_pid);
            close_fd(files);
            files[0] = for_next;
            files[1] = 1;
        }
    }
    cmd_destoy(cmd);
    return (pid);
}
