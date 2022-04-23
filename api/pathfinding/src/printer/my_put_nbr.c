/*
** EPITECH PROJECT, 2021
** B-CPE-100-LYN-1-1-cpoolday03-mathias.andre
** File description:
** my_put_nbr.c
*/

#include "my.h"

void my_putchar(char c);

static void print_nbr(long nbr)
{
    long n;

    if (nbr != 0) {
        if (nbr < 0) {
            n = nbr % 10 * -1;
        } else {
            n = nbr % 10;
        }
        print_nbr(nbr / 10);
        my_putchar(n + '0');
    }
}

static void my_put_nbr_util(long nbr)
{
    if (nbr == 0) {
        my_putchar('0');
        return;
    }
    print_nbr(nbr);
}

void my_put_nbr(int nbr)
{
    my_put_nbr_util(nbr);
}
