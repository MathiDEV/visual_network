/*
** EPITECH PROJECT, 2021
** ezredump
** File description:
** my_split.c
*/

#include "../include/my.h"

int in_charset(char c, char *charset)
{
    int i = -1;

    while (charset[++i])
        if (charset[i] == c)
            return (1);
    return (0);
}

static int wcount(char *str, char *charset)
{
    int i = 0;
    int count = 0;

    while (str[i]) {
        while (str[i] && in_charset(str[i], charset))
            i++;
        if (str[i] && !in_charset(str[i], charset))
            count++;
        while (str[i] && !in_charset(str[i], charset))
            i++;
    }
    return (count);
}

static char *wmalloc(char *str, char *charset)
{
    char *toa;
    int i = 0;

    while (str[i] && !in_charset(str[i], charset))
        i++;
    toa = malloc(sizeof(char) * i + 1);
    i = -1;
    while (str[++i] && !in_charset(str[i], charset))
        toa[i] = str[i];
    toa[i] = '\0';
    return (toa);
}

char **my_split(char *str, char *charset)
{
    int i = 0;
    int j = 0;
    char **arr;

    arr = malloc(sizeof(char *) * (wcount(str, charset) + 1));
    while (str[i]) {
        while (str[i] && in_charset(str[i], charset))
            i++;
        if (str[i] && !in_charset(str[i], charset))
            arr[j++] = wmalloc(&str[i], charset);
        while (str[i] && !in_charset(str[i], charset))
            i++;
    }
    arr[j] = 0;
    return (arr);
}
