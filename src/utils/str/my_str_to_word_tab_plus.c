/*
** EPITECH PROJECT, 2019
** str to word_tab plusplus
** File description:
** my_str_to_word_tab_plus
*/

#include "vec.h"
#include "sh.h"
#include <string.h>
#include <stdlib.h>

static int is_word(char *str1, char *str2)
{
    int i = 0;

    while (str2[i] != '\0') {
        if (str1[i] != str2[i] || str1[i] == '\0') {
            return (0);
        }
        i++;
    }
    return (1);
}

static int is_word_separator(char *str, char **word_separators)
{
    for (int i = 0; word_separators[i] != NULL; i++) {
        if (is_word(str, word_separators[i])) {
            return (i);
        }
    }
    return (-1);
}

static char *get_word_plus(char *str, char *separators,
    char **word_separators)
{
    int i = 0;
    char *word = NULL;

    if (is_word_separator(str, word_separators) != -1) {
        return (strdup(word_separators[is_word_separator(str,
            word_separators)]));
    }
    while (str[i] != '\0' && index_of(str[i], separators) == -1 &&
            is_word_separator(str + i, word_separators) == -1) {
        i++;
    }
    word = malloc(sizeof(char) * (i + 1));
    i = 0;
    while (str[i] != '\0' && index_of(str[i], separators) == -1 &&
            is_word_separator(str + i, word_separators) == -1) {
        word[i] = str[i];
        i++;
    }
    word[i] = '\0';
    return (word);
}

vec_t *my_str_to_word_tab_plus(char *str, char *separators,
    char **separator_and_word)
{
    vec_t *v = create_vec();
    char *word = NULL;

    while (*str != '\0') {
        while (*str != '\0' && index_of(*str, separators) != -1) {
            str++;
        }
        if (*str == '\0')
            return (v);
        word = get_word_plus(str, separators, separator_and_word);
        push(v, word);
        str = str + strlen(word);
    }
    return (v);
}