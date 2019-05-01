/*
** EPITECH PROJECT, 2019
** exit
** File description:
** exit
*/

#include "sh.h"
#include "vec.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int my_exit(vec_t *params, shell_t *shell)
{
    my_putstr("exit\n");
    if (params->element == 2) {
        shell->status = 0;
        exit(atoi(params->content[1]));
    } else {
        shell->status = 0;
        exit(shell->status);
    }
    return (0);
}