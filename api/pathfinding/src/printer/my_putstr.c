/*
** EPITECH PROJECT, 2021
** B-CPE-100-LYN-1-1-cpoolday04-mathias.andre
** File description:
** my_putstr.c
*/

#include "my.h"

int my_putstr(char *str)
{
    if (!str)
        return 0;
    int a = write(1, str, my_strlen(str));
    return (0);
}

void my_putnbr(int nb)
{
    if (nb < 0) {
        my_putchar('-');
        nb = -nb;
    }
    if (nb >= 10)
        my_putnbr(nb / 10);
    my_putchar(nb % 10 + '0');
}
