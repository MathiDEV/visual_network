/*
** EPITECH PROJECT, 2021
** B-CPE-200-LYN-2-1-lemin-valentin.dury
** File description:
** print_moves.c
*/

#include "my.h"

int get_ant_out(int n, int *ants, int ants_in_hill, int n_ants)
{
    int begin = n_ants - ants_in_hill;
    if (n > ants_in_hill)
        n = ants_in_hill;
    for (int i = begin; i < begin + n; i++)
        ants[i] = 1;
    return (n);
}

void print_ant_move(int ant_id, char *room_name, int last)
{
    my_putchar('P');
    my_put_nbr(ant_id);
    my_putchar('-');
    my_putstr(room_name);
    if (!last)
        my_putchar(' ');
}

void print_ant_moves(printer *dt, int *ants, char ***paths, int *path_len)
{
    print_ant_move(dt->ant_id + 1,
    paths[dt->ant_id % dt->n_paths][dt->this_begin],
    dt->ant_id == dt->n_ants - 1 || ants[dt->ant_id + 1] == 0);
    if (dt->this_begin == path_len[dt->ant_id % dt->n_paths] - 1) {
        dt->arrived_ants += 1;
        ants[dt->ant_id] = 2;
    }
}

void ant_loop(printer *dt, int *ants, char ***paths, int *path_len)
{
    dt->removed = get_ant_out(dt->n_paths, ants, dt->ants_in_hill, dt->n_ants);
    dt->ants_in_hill -= dt->removed;
    dt->ant_id = 0;
    dt->this_begin = dt->step_id;
    dt->step_id += 1;
    while (dt->ant_id < dt->n_ants && ants[dt->ant_id] != 0) {
        if (ants[dt->ant_id] != 2)
            print_ant_moves(dt, ants, paths, path_len);
        dt->ant_id += 1;
        if (dt->ant_id % dt->n_paths == 0 && dt->ant_id != 0)
            dt->this_begin -= 1;
    }
    my_putchar('\n');
}

void print_moves(int n_ants, char ***paths)
{
    printer dt;
    int *ants = malloc(sizeof(int) * n_ants);
    int n_paths = triple_strlen(paths);
    int path_len[n_paths];

    for (int i = 0; i < n_paths; i++)
        path_len[i] = double_strlen(paths[i]);
    dt.n_paths = n_worth_path(n_ants, n_paths, path_len);
    sort_by_len(n_paths, path_len, paths);
    dt.n_ants = n_ants;
    dt.ants_in_hill = n_ants;
    dt.arrived_ants = 0;
    dt.turn_first_step = 0;
    dt.step_id = 0;
    dt.removed = 0;
    dt.ant_id = 0;
    for (int i = 0; i < n_ants; i++)
        ants[i] = 0;
    while (dt.arrived_ants < n_ants)
        ant_loop(&dt, ants, paths, path_len);
}
