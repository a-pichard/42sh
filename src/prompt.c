/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** prompt
*/

#include "sh.h"
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

static int get_pathlen(char *path)
{
    int len = strlen(path);
    int i = 0;

    while (len > 0 && path[len] != '/') {
        len--;
        i++;
    }
    if (path[len] == '/') {
        i--;
    }
    return (i);
}

static int get_index(char *path)
{
    int pathlen = get_pathlen(path);
    int len = strlen(path);

    return (len - pathlen);
}

static char *get_filename(char *path)
{
    int index = get_index(path);
    int len = get_pathlen(path);
    char *filename = malloc(sizeof(char) * (len + 1));
    int i = 0;

    if (filename == NULL) {
        my_puterr("malloc error.\n");
        exit(84);
    }
    while (i != len) {
        filename[i] = path[index];
        i++;
        index++;
    }
    free(path);
    filename[i] = '\0';
    return (filename);
}

void prompt(void)
{
    char *current_dir;

    if (isatty(0) == 1) {
        my_putchar('[');
        my_putstr(getlogin());
        my_putstr("@localhost ");
        current_dir = get_filename(getcwd(NULL, 0));
        my_putstr(current_dir);
        free(current_dir);
        my_putstr("]$ ");
    }
}