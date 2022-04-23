/*
** EPITECH PROJECT, 2021
** B-CPE-200-LYN-2-1-lemin-valentin.dury
** File description:
** multiple_strlen.c
*/

int triple_strlen(char ***table)
{
    int i = 0;

    if (!table)
        return (0);
    for (; table[i]; i++)
        ;
    return (i);
}

int double_strlen(char **table)
{
    int i = 0;

    for (; table[i]; i++)
        ;
    return (i);
}
