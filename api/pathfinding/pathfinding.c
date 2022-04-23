/*
** EPITECH PROJECT, 2022
** lemin
** File description:
** lem_in_main
*/

#include "include/my.h"

void my_putstr_spec(char *str)
{
    int i = -1;
    int tmp = 0;

    while (str[++i] && str[i] != '\n')
        tmp = write(1, &str[i], 1);
    tmp = write(1, "\n", 1);
}

int print_sk(four_t *four)
{
    if (four->map[0] == NULL)
        return 0;
    my_putstr("#number_of_ants\n");
    my_putstr(four->map[0]);
    my_putstr("#rooms\n");
    return 1;
}

void print_trace(four_t *four, char ***ways, int *ret, int t)
{
    if (!print_sk(four))
        return;
    for (int i = 0; four->map[++i];) {
        if (t && four->nb_v != -1 && (four->nb_v <= i))
            break;
        if (t == 0 && has_dash(four->map[i])) {
            my_putstr("#tunnels\n");
            t++;
        }
        my_putstr_spec(four->map[i]);
    }
    if (!t)
        my_putstr("#tunnels\n");
    my_putstr("#moves\n");
    if (!four->b_err && ways) {
        print_moves(four->nb_four, ways);
        *ret = 0;
    }
}

int lem_in(void)
{
    room_t *start;
    four_t *four = get_fourmilliere();
    room_t *tmp;
    int ret = 84;
    char ***ways;

    tmp = four->rooms;
    if (!four->b_err) {
        create_graph(four);
        ways = build_ways(four);
        if (!triple_strlen(ways))
            four->b_err = 1;
    }
    print_trace(four, ways, &ret, 0);
    return ret;
}

int main(int argc, char *argv[])
{
    return (lem_in());
}
