/*
** EPITECH PROJECT, 2021
** ezredump
** File description:
** any_utils.c
*/

#include "../include/my.h"

int my_strcmp(char *s1, char *s2)
{
    int i = 0;

    if (!s1 || !s2)
        return (1);
    while (s1[i] && s2[i] && (s1[i] == s2[i]))
        i++;
    return (s1[i] - s2[i]);
}

int my_strlen(char *str)
{
    int i = 0;

    if (str == NULL)
        return (-1);
    while (str[i])
        i++;
    return (i);
}

char *my_strdup(char *str)
{
    int i = 0;
    char *new = malloc(sizeof(char) * (my_strlen(str) + 1));

    while (str[i]) {
        new[i] = str[i];
        i++;
    }
    new[i] = '\0';
    return (new);
}

int my_getnbr(char *str)
{
    long res = 0;
    int i = -1;

    if (str == NULL)
        return -1;
    while (str[++i] && str[i] != '\n') {
        if (str[i] >= '0' && str[i] <= '9') {
            res *= 10;
            res += str[i] - 48;
        } else
            return -1;
    }
    if (res > 2147483647 || res <= 0)
        return (-1);
    return (res);
}
