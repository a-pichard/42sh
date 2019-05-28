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

Test(separator, one_and1, .init=redirect_all_std)
{
    shell_t shell;
    shell.status = 0;
    shell.prev_dir = NULL;
    shell.alias = create_vec();

    exec_separator("echo salut && echo salut", &shell);
    cr_assert_stdout_eq_str("salut\nsalut\n");
}

Test(separator, one_and2, .init=redirect_all_std)
{
    shell_t shell;
    shell.status = 0;
    shell.prev_dir = NULL;
    shell.alias = create_vec();

    exec_separator("caca && echo salut; echo toto", &shell);
    cr_assert_stderr_eq_str("caca: Command not found.\n");
    cr_assert_stdout_eq_str("toto\n");
}

Test(separator, five_and, .init=redirect_all_std)
{
    shell_t shell;
    shell.status = 0;
    shell.prev_dir = NULL;
    shell.alias = create_vec();

    exec_separator("echo a && echo b && echo c && echo d && echo e", &shell);
    cr_assert_stdout_eq_str("a\nb\nc\nd\ne\n");
}