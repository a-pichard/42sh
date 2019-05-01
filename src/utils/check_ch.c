/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** chack_ch
*/

int check_ch(char c)
{
    if (c > 32 && c <= 126)
        return (1);
    else
        return (0);
}