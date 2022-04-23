/*
** EPITECH PROJECT, 2021
** B-CPE-100-LYN-1-1-cpoolday03-mathias.andre
** File description:
** my_putchar.c
*/

#include "my.h"

void my_putchar(char c)
{
    int a = write(1, &c, 1);
}
