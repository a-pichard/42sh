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

Test(separator, invalid1, .init=redirect_all_std)
{
    shell_t shell;
    shell.status = 0;
    shell.prev_dir = NULL;
    shell.alias = create_vec();

    exec_separator("echo salut ||", &shell);
    cr_assert_stderr_eq_str("Invalid null command.\n");
}

Test(separator, invalid2, .init=redirect_all_std)
{
    shell_t shell;
    shell.status = 0;
    shell.prev_dir = NULL;
    shell.alias = create_vec();

    exec_separator("echo salut ;||&&", &shell);
    cr_assert_stderr_eq_str("Invalid null command.\n");
}