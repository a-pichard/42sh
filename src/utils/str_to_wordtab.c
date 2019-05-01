/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** str_to_wordtab
*/

/*
** EPITECH PROJECT, 2019
** minishell1.c
** File description:
** str_to_wordtab
*/

#include "sh.h"
#include <stdlib.h>

int get_nb_word(char *str)
{
    int i = 0;
    int words = 0;

    if (check_ch(str[0]) == 1)
        words = 1;
    while (str[i] != '\0') {
        if (check_ch(str[i]) == 0 && check_ch(str[i + 1]) == 1)
            words++;
        i++;
    }
    return (words);
}

int get_word_len(char *str, int *j)
{
    int i = 0;

    while (check_ch(str[*j + i]) == 1) {
        i++;
    }
    return (i);
}

void skip_spaces(char *str, int *i)
{
    while (check_ch(str[*i]) == 0) {
        (*i)++;
    }
}

char *get_word(char *str, int *j)
{
    int i = 0;
    char *word;

    skip_spaces(str, j);
    word = malloc(sizeof(char) * (get_word_len(str, j) + 1));
    if (word == NULL)
        return (NULL);
    while (check_ch(str[*j]) == 1) {
        word[i] = str[*j];
        (*j)++;
        i++;
    }
    word[i] = '\0';
    return (word);
}

char **str_to_wordtab(char *str)
{
    int nb_word = get_nb_word(str);
    char **wordtab = malloc(sizeof(char *) * (nb_word + 1));
    int i = 0;
    int j = 0;

    if (wordtab == NULL)
        return (NULL);
    wordtab[nb_word] = NULL;
    while (i != nb_word) {
        wordtab[i] = get_word(str, &j);
        if (wordtab[i] == NULL)
            return (NULL);
        i++;
    }
    return (wordtab);
}