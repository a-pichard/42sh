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

static int get_index_arg(vec_t **arg, int redir, int j)
{
    int ret;

    if (arg[j] == NULL)
        ret = j;
    else if (arg[j]->element > 0 && redir && j > 0)
        ret = j - 1;
    else
        ret = j;
    if (arg[ret] == NULL)
        arg[ret] = create_vec();
    return (ret);
}

static void fill_my_struct(cmd_t *cmds, vec_t *splited_cmd)
{
    int i = 0;
    int j = 0;
    int index;
    char *oldsep = NULL;

    while (i != (int)splited_cmd->element) {
        if (!is_redirs((char *)splited_cmd->content[i])) {
            index = get_index_arg(cmds->cmd, is_redir(oldsep), j);
            push(cmds->cmd[index], strdup(splited_cmd->content[i]));
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

cmd_t *parser(char *line)
{
    cmd_t *cmds = xmalloc(sizeof(cmd_t));
    char *separators[] = SEPARATOR;
    vec_t *splited_cmd = my_str_to_word_tab_plus(line, " \t\n", separators);

    cmds->nb_cmd = get_nb_cmd(splited_cmd) + 2;
    mem_alloc_cmds(cmds);
    fill_my_struct(cmds, splited_cmd);
    destroy_vec(splited_cmd, free);
    return (cmds);
}