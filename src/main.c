/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** main
*/

#include "sh.h"

int main(void)
{
    shell_t shell;

    shell.status = 0;
    shell.prev_dir = NULL;
    myshell(&shell);
    return (0);
}
