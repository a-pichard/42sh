/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** parser_sep
*/

#include "sh.h"

vec_t *parser_sep(char *cmd)
{
    char *separators[] = {";", "||", "&&", NULL};
    vec_t *splited_cmd = my_str_to_word_tab_plus(cmd, "\n", separators);

    return (splited_cmd);
}