/*
** EPITECH PROJECT, 2019
** setenv
** File description:
** setenv
*/

#include "sh.h"
#include "vec.h"
#include <stdlib.h>

static int char_isalpha(char c)
{
    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <=  'z'))
        return (1);
    else if (c == '_')
        return (1);
    else {
        my_puterr("setenv: Variable name must begin with a letter.\n");
        return (0);
    }
}

static int char_isalpha_num(char c)
{
    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <=  'z') || c == '_')
        return (1);
    else if (c >= '0' && c <= '9')
        return (1);
    else {
        my_puterr("setenv: Variable name must contain");
        my_puterr(" alphanumeric characters.\n");
        return (0);
    }
}

static int my_str_isalpha(char const *str)
{
    int i = 0;

    if (char_isalpha(str[0]) == 0)
        return (0);
    while (str[i] != '\0') {
        if (char_isalpha_num(str[i]) == 0) {
            return (0);
        }
        i = i + 1;
    }
    return (1);
}

static int do_setenv(vec_t *info)
{
    if ((my_str_isalpha((char *)info->content[1])) == 0)
        return (1);
    if (info->element == 2)
        return (setenv((char *)info->content[1], "", 1));
    if (info->element == 3)
        return (setenv((char *)info->content[1], (char *)info->content[2], 1));
    
}

int my_setenv(vec_t *info, shell_t *shell)
{
    if (info->element == 1) {
        return (my_env(info, shell));
    } else if (info->element < 1 || info->element > 3) {
        my_puterr("setenv: Too many arguments.\n");
        shell->status = 1;
        return (1);
    }
    else {
        shell->status = do_setenv(info);
        return (shell->status);
    }
}