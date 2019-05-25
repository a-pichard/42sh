/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** test_str
*/

#include <criterion/criterion.h>
#include "vec.h"
#include "sh.h"

Test(str, str_to_word_tab)
{
    char *str = "ls -l\t \tsalut|echo";
    vec_t *vec_test = create_vec();
    vec_t *vec;
    char *separators[] = SEPARATOR;

    push(vec_test, "ls");
    push(vec_test, "-l");
    push(vec_test, "salut");
    push(vec_test, "|");
    push(vec_test, "echo");
    vec = my_str_to_word_tab_plus(str, " \t\n", separators);
    for (size_t i = 0; i < vec->element; i++) {
        char *element_test = get(vec_test, i);
        char *element_function = get(vec, i);
        cr_assert_str_eq(element_function, element_test);
    }
}

