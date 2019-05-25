/*
** EPITECH PROJECT, 2019
** unit_test
** File description:
** unit test
*/


#include <criterion/criterion.h>
#include "vec.h"

Test(vector, test_vector1)
{
    char *test1 = "salut";
    char *test2 = "caca";
    vec_t *vec = create_vec();

    push(vec, test1);
    cr_assert_eq(vec->element, 1);
    cr_assert_eq(vec->content[0], test1);
    push(vec, test2);
    cr_assert_eq(vec->element, 2);
    cr_assert_eq(vec->content[1], test2);
    set(vec, 1, test1);
    cr_assert_eq(vec->element, 2);
    cr_assert_eq(vec->content[1], test1);
    set(vec, 10, test1);
    cr_assert_eq(vec->element, 2);
    cr_assert_eq(vec->content[1], test1);
    pop(vec, 0, NULL);
    cr_assert_eq(vec->element, 1);
    cr_assert_eq(vec->content[1], NULL);
    char *cmp = get(vec, 100);
    cr_assert_eq(cmp, NULL);
}

Test(vector, test_vector2)
{
    vec_t *vec = create_vec();

    push(vec, strdup("salut"));
    push(vec, strdup("salut"));
    push(vec, strdup("salut"));
    pop(vec, 10, free);
    pop(vec, 0, free);
    free(vec->content[0]);
    pop(vec, 0, NULL);
    cr_assert_str_eq(vec->content[0], "salut");
    destroy_vec(vec, free);
}

Test(vector, test_vector3)
{
    vec_t *vec = NULL;

    destroy_vec(vec, free);
    vec = create_vec();
    cr_assert_not(vec == NULL);
    push(vec, strdup("salut"));
    push(vec, strdup("salut"));
    apply_on_vec(vec, free);
    destroy_vec(vec, NULL);
}
