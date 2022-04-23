/*
** EPITECH PROJECT, 2022
** lemin
** File description:
** frees
*/

#include "../include/my.h"

void free_chars(char **r)
{
    int i = 0;

    while (r[++i] != NULL)
        free(r[i]);
    free(r);
}
