/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** redirect_stdin
*/

#include "vec.h"
#include "sh.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int strcmp_without_return(char *str, char *str2)
{
    int j = 0;
    int pass = 0;

    for (int i = 0; str[i] != '\0' && str[j] != '\0'; i++, j++)
        if (str[i] == str2[i])
            pass++;
        else if (str[i] == '\n' || str[2] == '\n')
            pass += 0;
        else
            return (0);
    return (1);
}

static void get_user_stdin_input(int fd[2], UNUSED char *arg, vec_t *cmd)
{
    char *str = NULL;
    size_t n = 0;

    my_putstr("? ");
    while (42) {
        if (getline(&str, &n, stdin) < 1 || str == NULL ||
        strcmp_without_return((char *) cmd->content[0], str))
            break;
        my_putstr("? ");
        if (write(fd[1], str, strlen(str)) == -1)
            perror("write");
    }
}

int redirect_stdin_double(void *tmp, int files[2], vec_t *cmd)
{
    if (pipe(files) == -1)
        perror("pipe");
    get_user_stdin_input(files, tmp, cmd);
    dup2(files[0], 0);
    close(files[1]);
    return (1);
}