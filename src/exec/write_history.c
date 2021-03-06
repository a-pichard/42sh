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

    if (!n)
        return ("0");
    for (i = 0; n > 0; i += 1) {
        dest[i] = n % 10 + 48;
        n = n / 10;
    }
    dest[i] = '\0';
    return (my_revstr(dest));
}

void my_time(FILE *file)
{
    time_t now = time(NULL);
    struct tm *now_tm = localtime(&now);
    char *hour = int_to_str(now_tm->tm_hour);
    char *min = int_to_str(now_tm->tm_min);

    if (strlen(hour) == 1)
        hour = my_realloc("0", hour);
    if (strlen(min) == 1)
        min = my_realloc("0", min);
    fprintf(file, "%s:%s", hour, min);
    free(min);
    free(hour);
}

void nb_history(char *str, int line, FILE *file)
{
    char *nb = int_to_str(line);

    for (int i = 0; i < 6 - (int) strlen(nb) - 1; i += 1)
        fprintf(file, " ");
    free(nb);
    fprintf(file, "%d  ", line);
    my_time(file);
    fprintf(file, "   %s", str);
    if (str[strlen(str) - 1] != '\n')
        fprintf(file, "\n");
    fclose(file);
}

void write_history(char *str)
{
    FILE *file;
    char *mem = NULL;
    int line = 0;
    int fd = open(".42history", O_WRONLY | O_APPEND | O_CREAT, 0664);

    if (fd != -1) {
        write(fd, " ", 1);
        close(fd);
    }
    file = fopen(".42history", "r");
    if (!strlen(str))
        return;
    for (size_t size = 0; file != NULL &&
            getline(&mem, &size, file) != -1; size = 0)
        line += 1;
    if (file != NULL) {
        fclose(file);
        file = fopen(".42history", "a");
        nb_history(str, line, file);
    }
}
