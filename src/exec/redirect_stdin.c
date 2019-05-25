/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** redirect_stdin
*/

#include "sh.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>

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

int redirect_stdin_double(void *tmp, int files[2])
{
    if (pipe(files) == -1)
        perror("pipe");
    get_user_stdin_input(files, tmp);
    dup2(files[0], 0);
    close(files[1]);
    return (1);
}