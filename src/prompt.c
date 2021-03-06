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
#include <stdio.h>

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

char *myrealloc(char *old, char c)
{
    char *str = xmalloc(sizeof(char) * 2);

    free(old);
    str[0] = c;
    str[1] = '\0';
    return (str);
}

static char *check_home(char *path, char *fn)
{
    char *home = getenv("HOME");
    int ret;

    if (home != NULL) {
        ret = strcmp(path, home);
        if (ret == 0) {
            free(path);
            fn = myrealloc(fn, '~');
        } else if (ret < 0) {
            free(fn);
            fn = path;
        } else
            free(path);
    } else {
        free(path);
    }
    if (strlen(fn) == 0)
        fn = myrealloc(fn, '/');
    return (fn);
}

static char *get_filename(char *path)
{
    int len = get_pathlen(path);
    int index = (strlen(path) - len);
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
    filename[i] = '\0';
    return (check_home(path, filename));
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
