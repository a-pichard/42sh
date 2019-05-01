/*
** EPITECH PROJECT, 2019
** unsetenv
** File description:
** unsetenv
*/

#include "sh.h"
#include "vec.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

int my_unsetenv(vec_t *params, shell_t *shell)
{
    int status = 0;

    if (params->element == 1) {
        my_puterr("unsetenv: Too few arguments.\n");
        shell->status = 1;
        return (1);
    }
    for (int i = 0; i != params->element && status != -1; i += 1)
        status = unsetenv((char *)params->content[i]);
    if (status == -1) {
        perror("unsetenv:");
        shell->status = 1;
        return (1);
    }
    shell->status = 0;
    return (0);
}
