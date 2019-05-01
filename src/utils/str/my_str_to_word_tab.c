/*
** EPITECH PROJECT, 2019
** my_str_to_word_tab
** File description:
** my_str_to_word_tab
*/

#include "vec.h"
#include "sh.h"
#include <stdlib.h>
#include <string.h>
#include <string.h>

static char *get_word(char *str, char *separators)
{
    int i = 0;
    char *word = NULL;

    while (str[i] != '\0' && index_of(str[i], separators) == -1) {
        i++;
    }
    word = malloc(sizeof(char) * (i + 1));
    i = 0;
    while (str[i] != '\0' && index_of(str[i], separators) == -1) {
        word[i] = str[i];
        i++;
    }
    word[i] = '\0';
    return (word);
}

vec_t *my_str_to_word_tab(char *str, char *separators)
{
    vec_t *v = create_vec();
    char *word = NULL;

    if (str == NULL)
        return (NULL);
    while (*str != '\0') {
        while (*str != '\0' && index_of(*str, separators) != -1) {
            str++;
        }
        if (*str == '\0')
            return (v);
        word = get_word(str, separators);
        push(v, word);
        str = str + strlen(word);
    }
    return (v);
}
