/*
** EPITECH PROJECT, 2019
** exit
** File description:
** exit
*/

#include "sh.h"
#include "vec.h"
#include <stdlib.h>
#include <unistd.h>

int my_exit(vec_t *params, shell_t *shell)
{
    my_putstr("exit\n");
    if (params->element == 2)
        exit(atoi(params->content[1]));
    else
        exit(shell->status);
    return (0);
}