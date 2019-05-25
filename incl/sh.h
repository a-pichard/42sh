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
#ifdef __BONUS__
#define BONUS 1
#else
#define BONUS 0
#endif
#define SEPARATOR {";", "||", "&&", "|", ">>", "<<", ">", "<", NULL}
#define FUNCTION_PTR {my_env, my_setenv, my_unsetenv, my_exit, my_cd, \
    my_echo, my_alias, my_which, my_where, NULL};
#define COMMAND_STR {"env", "setenv", "unsetenv", "exit", "cd", "echo",\
    "alias", "which", "where", NULL};

int puterr_str(char *str, char *err, int ret);
int puterr_nb(int nb, char *err, int ret);
int my_atoi_f(char *str, int n);
int my_atoi_d(char *str);
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
char *my_strcat(const char *src, const char *src_bis);
char *vec_to_str(vec_t *cmd);
char *int_to_str(int n);
char *space_to_point(char *str);

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
void init_shell(shell_t *shell);
void close_fd(int files[2]);
bool or(shell_t *shell);
bool and(shell_t *shell);
bool semicolon(UNUSED shell_t *shell);

//command
int redirect_stdin_double(void *tmp, int files[2], vec_t *cmd);
int command(vec_t *command, shell_t *shell, int files[2]);
vec_t *redirection(vec_t *commands, shell_t *shell);
cmd_t *parser(vec_t *splited_cmd);
void handle_sigint(int sig);
int is_redirs(char *str);
bool is_redir(const char *str);
vec_t *parser_sep(char *cmd);
void print_err(int s, shell_t *shell);
void my_exiterr(char *str, char *err, int n);
bool getglob(vec_t **cmd, int *status);
char *myrealloc(char *old, char c);
void exec(char *str, shell_t *shell);
void exec_separator(char *str, shell_t *shell);
void write_history(char *str);
char *history(char *str);

//builtin
char *my_realloc(char *str, char *src);
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
int my_where(vec_t *params, shell_t *shell);
vec_t *replace_alias(vec_t *cmd, shell_t *shell);
int value_echo(char *str);

#endif
