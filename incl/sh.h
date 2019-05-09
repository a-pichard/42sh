/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** sh
*/

#ifndef SH_H_
#define SH_H_
#include "vec.h"
#define SEPARATOR {";", "||", "&&", "|", ">>", "<<", ">", "<", NULL}

int my_atoi(char *str);
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
void my_putnbr(int n);
char *my_strcat(char *src, char *src_bis);

typedef struct {
    int nb_cmd;
    vec_t **cmd;
    vec_t *sep;
} cmd_t;


struct shell_s
{
    int status;
    char *prev_dir;
};

typedef struct shell_s shell_t;
void myshell(shell_t *shell);
void prompt(void);
//command
int command(vec_t *command, shell_t *shell);
//builtin
int my_cd(vec_t *params, shell_t *shell);
int cd_with_args(vec_t *params, shell_t *shell);
void check_dir(char *path, char *temp_prev);
int my_env(vec_t *params, shell_t *shell);
int my_setenv(vec_t *params, shell_t *shell);
int my_unsetenv(vec_t *params, shell_t *shell);
int my_exit(vec_t *params, shell_t *shell);
void my_exiterr(char *str, char *err, int n);
int my_echo(vec_t *params, shell_t *shell);
char *value_env(char *str);
int pars_env(char *str);
void handle_sigint(int sig);
int is_redirs(char *str);
int is_redir(char *str);

#endif
