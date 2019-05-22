/*
** EPITECH PROJECT, 2019
** write_history.c
** File description:
** write history
*/

#include "sh.h"
#include "vec.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

char *my_revstr(char *str)
{
    int i = 0;
    int j = 0;
    char memo[2] = {0};

    while (str[i] != '\0')
        i += 1;
    while (j < i / 2) {
        memo[0] = str[j];
        str[j] = str[i - j - 1];
        str[i - j - 1] = memo[0];
        j += 1;
    }
    return (str);
}

char *int_to_str(int n)
{
    char *dest = xmalloc(sizeof(char) * 6);
    int i;

    for (i = 0; n > 0; i += 1) {
        dest[i] = n % 10 + 48;
        n = n / 10;
    }
    dest[i] = '\0';
    return (my_revstr(dest));
}

void my_time(int fd)
{
    time_t now = time(NULL);
    struct tm *now_tm = localtime(&now);
    char *hour = int_to_str(now_tm->tm_hour);
    char *min = int_to_str(now_tm->tm_min);
    char d = ':';

    write(fd, hour, 2);
    write(fd, &d, 1);
    write(fd, min, 2);
    free(hour);
    free(min);
}

void nb_history(char *str, int line, FILE *file, int fd)
{
    char *nb = int_to_str(line);
    char s = ' ';

    for (int i = 0; i < 6 - (int) strlen(nb); i += 1)
        write(fd, &s, 1);
    write(fd, nb, (int) strlen(nb));
    write(fd, &s, 1);
    write(fd, &s, 1);
    my_time(fd);
    write(fd, &s, 1);
    write(fd, &s, 1);
    write(fd, &s, 1);
    write(fd, str, (int) strlen(str));
    free(nb);
    if (str[strlen(str) - 1] != '\n')
        write(fd, "\n", 1);
    (file != NULL) ? fclose(file) : 0;
    close(fd);
}

void write_history(char *str)
{
    FILE *file = fopen(".42history", "r");
    int fd = open(".42history", O_CREAT | O_WRONLY | O_APPEND, 0664);
    char *mem = NULL;
    int line = 1;
    size_t size = 0;

    if (!strlen(str))
        return;
    if (fd == -1)
        my_puterr("open err\n");
    while (file != NULL && getline(&mem, &size, file) != -1) {
        line += 1;
        size = 0;
    }
    nb_history(str, line, file, fd);
}
