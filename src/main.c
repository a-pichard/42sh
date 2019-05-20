/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** main
*/

#include "sh.h"
#include <signal.h>

int main(void)
{
    shell_t shell;

    shell.status = 0;
    shell.prev_dir = NULL;
    shell.alias = create_vec();
    signal(SIGINT, handle_sigint);
    init_shell(&shell);
    myshell(&shell);
    return (0);
}
