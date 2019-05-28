/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** test_cd
*/

#include "sh.h"
#include "test.h"
#include <unistd.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>

Test(buildin, cd1, .init=redirect_all_std)
{
    shell_t shell;
    vec_t *params = create_vec();
    char *my_pwd = calloc(sizeof(char), 100);

    shell.status = 0;
    shell.prev_dir = NULL;
    shell.alias = create_vec();
    push(params, strdup("cd"));
    push(params, strdup("/etc"));
    my_cd(params, &shell);
    
    my_pwd = getcwd(my_pwd, 100);
    cr_assert_str_eq(my_pwd, "/etc");
}

Test(buildin, cd2, .init=redirect_all_std)
{
    shell_t shell;
    vec_t *params = create_vec();
    char *my_pwd = calloc(sizeof(char), 100);
    char *old_pwd = calloc(sizeof(char), 100);

    shell.status = 0;
    shell.prev_dir = NULL;
    shell.alias = create_vec();
    old_pwd = getcwd(old_pwd, 100);
    push(params, strdup("cd"));
    push(params, strdup("/var"));

    my_cd(params, &shell);
    my_pwd = getcwd(my_pwd, 100);
    cr_assert_str_eq(my_pwd, "/var");
    pop(params, 1, free);
    push(params, strdup("-"));
    my_cd(params, &shell);
    my_pwd = getcwd(my_pwd, 100);
    cr_assert_str_eq(my_pwd, old_pwd);
}