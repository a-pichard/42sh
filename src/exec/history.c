/*
** EPITECH PROJECT, 2019
** history.c
** File description:
** history
*/

#include "sh.h"
#include "vec.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

vec_t *put_hist(vec_t *cmd, int i, char *line, int *br)
{
    char *dest = xmalloc(sizeof(char) * strlen((char *)cmd->content[i]));
    int j;

    *br += 1;
    for (j = 0; ((char *)cmd->content[i])[j] != '!'; j += 1)
        dest[j] = ((char *)cmd->content[i])[j];
    dest[j] = '\0';
    for (int i = 0; i < 16; i += 1)
        line++;
    dest = my_realloc(dest, line);
    dest[strlen(dest) - 1] = '\0';
    cmd->content[i] = dest;
    return (cmd);
}

int pars_nb(int nb, vec_t **file)
{
    int n;

    if (nb >= 0 || file == NULL)
        return (nb);
    n = my_atoi_d((char *)(*file)->content[(*file)->element - 1]);
    nb = nb % (n + 1);
    if (nb == 0) {
        *file = NULL;
        return (0);
    }
    return (n + 1 + nb);
}

int pars_history(vec_t *cmd, vec_t *file, int i, int *mem)
{
    int nb = 0;
    int br = 0;

    for (int j = 0; ((char *)cmd->content[i])[j]; j += 1) {
        nb = 0;
        if (((char *)cmd->content[i])[j] == '!' &&
            (nb = my_atoi_f((char *)cmd->content[i], j + 1)) == -666)
            return (puterr_str((char *)cmd->content[i],
                ": Event not found.\n", 1));
        br = 0;
        if ((nb && !file) || (nb && !(nb = pars_nb(nb, &file)) && file == NULL))
            return (puterr_nb(nb, ": Event not found.\n", 1));
        for (int k = 0; nb && k < (int)file->element; k += 1) {
            (nb == my_atoi_d((char *)file->content[k])) ?
                cmd = put_hist(cmd, i, (char *)file->content[k], &br) : 0;
        }
        if (nb && !br)
            return (puterr_nb(nb, ": Event not found.\n", 1));
        (nb) ? *mem = 0 : 0;
    }
    return (0);
}

static int valid(vec_t *cmd, int i)
{
    for (int j = 0; ((char *)cmd->content[i])[j]; j += 1) {
        if (((char *)cmd->content[i])[j] == '!' &&
            ((char *)cmd->content[i])[j + 1] == '\0')
            return (puterr_str("!", ": Command not found.\n", 1));
        if (((char *)cmd->content[i])[j] == '!' &&
            ((char *)cmd->content[i])[j + 1] != '\0' &&
            ((char *)cmd->content[i])[j + 1] == '-' &&
            ((char *)cmd->content[i])[j + 2] == '\0')
            return (puterr_str("!", ": Command not found.\n", 1));
    }
    return (0);
}

char *history(char *str)
{
    char *separators[] = {NULL};
    vec_t *cmd = my_str_to_word_tab_plus(str, " \t\n", separators);
    vec_t *file = create_vec();
    FILE *fd = fopen(".42history", "r");
    char *mem = NULL;
    size_t s = 0;
    int n = 1;

    for (;fd != NULL && getline(&mem, &s, fd) != -1; s = 0)
        push(file, mem);
    (fd != NULL) ? fclose(fd) : 0;
    (fd == NULL) ? file = NULL : 0;
    for (int i = 0; i < (int) cmd->element; i += 1)
        if (valid(cmd, i) || pars_history(cmd, file, i, &n))
            return (NULL);
    for (int i = 0; !n && i < (int) cmd->element; i += 1) {
        my_putstr((char *)cmd->content[i]);
        (i + 1 < (int) cmd->element) ? my_putchar(' ') : my_putchar('\n');
    }
    return (vec_to_str(cmd));
}
