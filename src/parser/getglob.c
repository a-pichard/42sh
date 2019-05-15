/*
** EPITECH PROJECT, 2019
** glob
** File description:
** getglob
*/

#include "vec.h"
#include "sh.h"
#include <glob.h>
#include <string.h>
#include <stdlib.h>

static int is_wildcard(char *str)
{
    int i = 0;

    while (str[i] != '\0') {
        if (str[i] == '*' || str[i] == '?' || str[i] == '[' || str[i] == ']')
            return (1);
        i++;
    }
    return (0);
}

static bool do_glob(vec_t *parsed, char *arg)
{
    glob_t glb;
    int r;
    bool ret;

    r = glob(arg, 0, NULL, &glb);
    if (!r) {
        for (int j = 0; j < (int)glb.gl_pathc; j++)
            push(parsed, strdup((char *)glb.gl_pathv[j]));
        ret = false;
    } else {
        ret = true;
    }
    globfree(&glb);
    return (ret);
}

bool getglob(vec_t **cmd)
{
    vec_t *parsed = create_vec();
    int  i = 0;
    int nb_wildcard = 0;
    int err = 0;

    while (i < (int)(*cmd)->element && (*cmd)->content[i] != NULL) {
        if (!is_wildcard((char *)(*cmd)->content[i])) {
            push(parsed, strdup((char *)(*cmd)->content[i]));
        } else {
            err += do_glob(parsed, (char *)(*cmd)->content[i]);
            nb_wildcard++;
        }
        i++;
    }
    push(parsed, NULL);
    destroy_vec(*cmd, free);
    *cmd = parsed;
    return ((nb_wildcard == err) ? true : false);
}