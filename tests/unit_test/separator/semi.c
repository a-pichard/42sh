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


Test(separator, one_semi, .init=redirect_all_std)
{
    shell_t shell;
    shell.status = 0;
    shell.prev_dir = NULL;
    shell.alias = create_vec();

    exec_separator("echo a ; echo b", &shell);
    cr_assert_stdout_eq_str("a\nb\n");
}

Test(separator, five_semi, .init=redirect_all_std)
{
    shell_t shell;
    shell.status = 0;
    shell.prev_dir = NULL;
    shell.alias = create_vec();

    exec_separator("echo a ; echo b ; echo c ; echo d ; echo e", &shell);
    cr_assert_stdout_eq_str("a\nb\nc\nd\ne\n");
}