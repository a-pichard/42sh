/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** sh
*/

#ifndef SH_H_
#define SH_H_
#include "vec.h"
#define SEPARATOR {";", "|", ">>", "<<", ">", "<", NULL}
extern char **environ;

void my_putchar(char c);
void my_putstr(char const *str);
void my_puterr(char const *str);
int get_tab_len(char **tab);
void print_tab(char **wordtab);
void destroy_tab(char **wordtab);
char **tabdup(char **env);
void *xmalloc(int);
int index_of(char c, char *tab);
int index_of_str(char *str, char **tab);
vec_t *my_str_to_word_tab_plus(char *str, char *separators,
    char **separator_and_word);

struct shell_s
{
    int status;
};
typedef struct shell_s shell_t;

int command(vec_t *command, shell_t *shell);

//builtin
int my_cd(vec_t *params, shell_t *shell);
int my_env(vec_t *params, shell_t *shell);
int my_setenv(vec_t *params, shell_t *shell);
int my_unsetenv(vec_t *params, shell_t *shell);
int my_exit(vec_t *params, shell_t *shell);
int my_echo(vec_t *params, shell_t *shell);



#endif