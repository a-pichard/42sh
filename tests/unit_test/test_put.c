/*
** EPITECH PROJECT, 2019
** unit_test
** File description:
** unit test
*/


#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "sh.h"
#include "test.h"

Test(put, putchar, .init=redirect_all_std)
{
    my_putchar('a');
    cr_assert_stdout_eq_str("a");
}

Test(put, putstr, .init=redirect_all_std)
{
    my_putstr("salut");
    cr_assert_stdout_eq_str("salut");
}

Test(put, puterr, .init=redirect_all_std)
{
    my_puterr("salut");
    cr_assert_stderr_eq_str("salut");
}

Test(put, putnbr, .init=redirect_all_std)
{
    my_putnbr(0);
    my_putnbr(5);
    my_putnbr(50456879);
    my_putnbr(-8);
    my_putnbr(-50);
    cr_assert_stdout_eq_str("0550456879-8-50");
}