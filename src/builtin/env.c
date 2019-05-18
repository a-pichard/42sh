/*
** EPITECH PROJECT, 2019
** env
** File description:
** env
*/

#include "sh.h"
#include "vec.h"
#include <string.h>
#include <unistd.h>

int my_env(UNUSED vec_t *info, shell_t *shell)
{
    extern char **environ;

    for (int i = 0; environ[i] != NULL; i++) {
        write(1, environ[i], strlen(environ[i]));
        write(1, "\n", 1);
    }
    shell->status = 0;
    return (0);
}
