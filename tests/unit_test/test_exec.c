/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** test_exec
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "vec.h"
#include "sh.h"

void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(exec, echo_pipe, .init=redirect_all_std)
{
    shell_t shell;
    char *str = strdup("echo bite | cat -e");

    shell.status = 0;
    shell.prev_dir = NULL;
    shell.alias = create_vec();
    exec(str, &shell);
    cr_assert_stdout_eq_str("bite$\n");
    cr_assert(1);
}