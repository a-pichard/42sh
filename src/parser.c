/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** parser
*/

#include "sh.h"
#include <stdlib.h>
#include <string.h>

static int get_nb_cmd(vec_t *cmd)
{
    int i = 0;
    int j = 0;

    while (i != (int)cmd->element) {
        if (is_redirs((char *)cmd->content[i]))
            j++;
        i++;
    }
    return (j);
}

static void fill_my_struct(cmd_t *cmds, vec_t *splited_cmd)
{
    int i = 0;
    int j = 0;
    char *oldsep = NULL;

    while (i != (int)splited_cmd->element) {
        if (!is_redirs((char *)splited_cmd->content[i])) {
            if (cmds->cmd[j] == NULL)
                cmds->cmd[j] = create_vec();
            if (cmds->cmd[j]->element > 0 && is_redir(oldsep) && j > 0) {
                if (cmds->cmd[j - 1] == NULL)
                    cmds->cmd[j - 1] = create_vec();
                push(cmds->cmd[j - 1], strdup(splited_cmd->content[i]));
            } else {
                push(cmds->cmd[j], strdup(splited_cmd->content[i]));
            }
        } else {
            push(cmds->sep, strdup(splited_cmd->content[i]));
            oldsep = (char *)splited_cmd->content[i];
            j++;
        }
        i++;
    }
}

static void mem_alloc_cmds(cmd_t *cmds)
{
    int i = 0;

    cmds->cmd = xmalloc(sizeof(vec_t *) * (cmds->nb_cmd));
    cmds->sep = create_vec();
    while (i != cmds->nb_cmd) {
        cmds->cmd[i] = NULL;
        i++;
    }
}

cmd_t *parser(vec_t *splited_cmd)
{
    cmd_t *cmds = xmalloc(sizeof(cmd_t));
    char *separators[] = SEPARATOR;

    cmds->nb_cmd = get_nb_cmd(splited_cmd) + 2;
    mem_alloc_cmds(cmds);
    fill_my_struct(cmds, splited_cmd);
    return (cmds);
}