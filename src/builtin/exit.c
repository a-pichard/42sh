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
    int dest;

    if (params->element == 2)
        dest = my_atoi(params->content[1]);
    if (params->element > 2 || dest == -666) {
        my_puterr("exit: Invalid syntax.\n");
        shell->status = 1;
    } else {
        my_putstr("exit\n");
        if (dest >= 0)
            exit(dest % 256);
        else
            exit(256 + (dest % 256));
    }
    return (0);
}
