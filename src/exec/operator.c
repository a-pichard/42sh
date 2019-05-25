/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** operator
*/

#include "sh.h"

bool or(shell_t *shell)
{
    if (shell->status == 0) {
        return (false);
    }
    return (true);
}

bool and(shell_t *shell)
{
    if (shell->status == 0) {
        return (true);
    }
    return (false);
}

bool semicolon(UNUSED shell_t *shell)
{
    return (true);
}