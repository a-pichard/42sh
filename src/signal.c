/*
** EPITECH PROJECT, 2019
** signal.c
** File description:
** signal
*/

#include "sh.h"
#include <signal.h>

void handle_sigint(int sig)
{
    if (sig == SIGINT) {
        my_putstr("\n");
        prompt();
    }
}
