/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** sh
*/

#ifndef SH_H_
#define SH_H_

void my_putchar(char c);
void my_putstr(char const *str);
void my_puterr(char const *str);
int get_tab_len(char **tab);
void print_tab(char **wordtab);
void destroy_tab(char **wordtab);
char **tabdup(char **env);

#endif