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

static void destroy(vec_t *params, shell_t *shell)
{
    destroy_vec(params, free);
    if (shell->prev_dir != NULL)
        free(shell->prev_dir);
}

int my_exit(vec_t *params, shell_t *shell)
{
    int dest = 0;

    if (params->element == 2)
        dest = my_atoi(params->content[1]);
    if (params->element > 2 || dest == -666) {
        my_puterr("exit: Invalid syntax.\n");
        shell->status = 1;
    } else if (params->element == 2) {
        my_putstr("exit\n");
        destroy(params, shell);
        if (dest >= 0)
            exit(dest % 256);
        else
            exit(256 + (dest % 256));
    }
    if (params->element == 1) {
        destroy(params, shell);
        my_putstr("exit\n");
        exit(0);
    }
    return (0);
}