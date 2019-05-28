/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** test_echo
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "test.h"
#include "sh.h"
#include "vec.h"

Test(echo, simple_echo, .init=redirect_all_std)
{
    shell_t shell;
    vec_t *params = create_vec();

    shell.status = 0;
    shell.prev_dir = NULL;
    shell.alias = create_vec();
    push(params, "echo");
    push(params, "salut");
    my_echo(params, &shell);
    cr_assert_stdout_eq_str("salut\n");
}

Test(echo, env_echo, .init=redirect_all_std)
{
    shell_t shell;
    vec_t *params = create_vec();

    shell.status = 0;
    shell.prev_dir = NULL;
    shell.alias = create_vec();
    push(params, "echo");
    push(params, "$COLORTERM");
    my_echo(params, &shell);
    cr_assert_stdout_eq_str("truecolor\n");
}

Test(echo, point_to_space)
{
    char *str = strdup("salut:salut");

    space_to_point(str);
    cr_assert_str_eq(str, "salut salut");
}