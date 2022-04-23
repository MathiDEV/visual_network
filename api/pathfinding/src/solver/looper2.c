/*
** EPITECH PROJECT, 2022
** lemin
** File description:
** parse_standard
*/

#include "../../include/my.h"

int struct_len(room_t **room)
{
    int i = 0;

    while (room[i]) {
        i++;
    }
    return (i);
}

int find_actual_pos(int id_way, room_t *room)
{
    int i = 0;

    while (room->neighbours[i]) {
        if (room->neighbours[i]->way == id_way)
            return (i);
        i++;
    }
    return (0);
}

int insert_multiway(four_t *four, t_list **actual_way)
{
    int nbway = road(-1);
    int totallen = 0;
    int pos = 0;
    t_list *last = NULL;

    while (bfs(four->start)) {
        totallen += size(-1);
        finish(0);
        pos = find_actual_pos(nbway, four->start);
        last = my_list_push_back(actual_way, nbway, last);
        last->g_cost = size(-1);
        last->from = pos;
        nbway++;
        road(nbway);
    }
    return (totallen);
}

void is_it_good(t_list *actual_way, t_list **best_way, int totlen, int *maxlen)
{
    if (my_list_size(actual_way) >= my_list_size(*best_way)) {
        if (totlen < *maxlen || *maxlen == 0) {
            *best_way = my_list_dup(actual_way);
            *maxlen = totlen;
        }
    }
}

int highest(t_list *before)
{
    if (!before)
        return (0);
    t_list *list = before;
    int data = list->g_cost;
    t_list *min = list;

    while (list) {
        if (data < list->g_cost) {
            min = list;
            data = list->g_cost;
        }
        list = list->next;
    }
    return (min->from);
}
