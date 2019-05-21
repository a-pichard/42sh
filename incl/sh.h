/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** sh
*/

#ifndef SH_H_
#define SH_H_
#include "vec.h"
#include <stdbool.h>
#ifdef __GNUC__
#define UNUSED __attribute__((unused))
#else
#define UNUSED //nothing
#endif
#define SEPARATOR {";", "||", "&&", "|", ">>", "<<", ">", "<", NULL}
#define FUNCTION_PTR {my_env, my_setenv, my_unsetenv, my_exit, my_cd, my_echo, my_alias, NULL};

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

typedef struct {
    char *alias;
    char *cmd;
} alias_t;

struct shell_s
{
    int status;
    char *prev_dir;
    vec_t *alias;
};

typedef struct shell_s shell_t;
//shell
void myshell(shell_t *shell);
void prompt(void);

void close_fd(int files[2]);

//command
int command(vec_t *command, shell_t *shell, int files[2]);
vec_t *redirection(vec_t *commands, shell_t *shell);
cmd_t *parser(vec_t *splited_cmd);
void handle_sigint(int sig);
int is_redirs(char *str);
bool is_redir(const char *str);
vec_t *parser_sep(char *cmd);
void print_err(int s, shell_t *shell);
void my_exiterr(char *str, char *err, int n);
bool getglob(vec_t **cmd);
char *myrealloc(char *old, char c);
void exec(char *str, shell_t *shell);
void exec_separator(char *str, shell_t *shell);

//builtin
int my_cd(vec_t *params, shell_t *shell);
int cd_with_args(vec_t *params, shell_t *shell);
void check_dir(char *path, char *temp_prev);
int my_env(vec_t *params, shell_t *shell);
int my_setenv(vec_t *params, shell_t *shell);
int my_unsetenv(vec_t *params, shell_t *shell);
int my_exit(vec_t *params, shell_t *shell);
int my_echo(vec_t *params, shell_t *shell);
char *value_env(char *str);
int pars_env(char *str);
int my_alias(vec_t *params, shell_t *shell);
int my_which(vec_t *params, shell_t *shell);
vec_t *replace_alias(vec_t *cmd, shell_t *shell);

#endif
