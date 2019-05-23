/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** test_separator
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "sh.h"
#include "test.h"

Test(test_semi_col, separator, .init=redirect_all_std)
{
    shell_t shell;
    shell.status = 0;
    shell.prev_dir = NULL;
    shell.alias = create_vec();

    exec_separator("echo salut ; echo salut", &shell);
    cr_assert_stdout_eq_str("salut\nsalut\n");
}

Test(test_semi_and1, separator, .init=redirect_all_std)
{
    shell_t shell;
    shell.status = 0;
    shell.prev_dir = NULL;
    shell.alias = create_vec();

    exec_separator("echo salut && echo salut", &shell);
    cr_assert_stdout_eq_str("salut\nsalut\n");
}

Test(test_semi_and2, separator, .init=redirect_all_std)
{
    shell_t shell;
    shell.status = 0;
    shell.prev_dir = NULL;
    shell.alias = create_vec();

    exec_separator("ls .salut && echo salut", &shell);
    cr_assert_stdout_eq_str("");
}