/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** close_fd
*/

#include <unistd.h>

void close_fd(int files[2])
{
    if (files[0] != 0)
        close(files[0]);
    if (files[1] != 1)
        close(files[1]);
}