/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** test_atoi
*/

#include <criterion/criterion.h>
#include "sh.h"

Test(atoi, my_atoi)
{
    long r = my_atoi("45");
    cr_assert_eq(r, 45);
    r = my_atoi("-42");
    cr_assert_eq(r, -42);
    r = my_atoi("a");
    cr_assert_eq(r, -666);
}

Test(atoi, my_atoi_f)
{
    long r = my_atoi_f("a45", 1);
    cr_assert_eq(r, 45);
    r = my_atoi_f("a45a", 1);
    cr_assert_eq(r, -666);
    r = my_atoi_f("a0", 1);
    cr_assert_eq(r, -666);
}

Test(atoi, my_atoi_d)
{
    long r = my_atoi_d("aa+aa45");
    cr_assert_eq(r, 45);
}