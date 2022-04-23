/*
** EPITECH PROJECT, 2022
** lemin
** File description:
** parse_standard
*/

#include "../../include/my.h"

void reset_way(room_t *room, int id)
{
    int i = 0;

    room->way = 0;
    while (room->neighbours[i]) {
        if (room->neighbours[i]->way == id) {
            room->neighbours[i]->way = 0;
            room = room->neighbours[i];
            i = 0;
        } else
            i++;
    }
}

void reset_all_way(four_t *four)
{
    int id = 0;
    int i = 0;
    room_t *room = four->start;

    while (four->start->neighbours[i]) {
        if (four->start->neighbours[i]->way != 0) {
            id = four->start->neighbours[i]->way;
            reset_way(four->start->neighbours[i], id);
        }
        i++;
    }
}

void set_best_way(four_t *four, t_list *best_way)
{
    t_list *useless = NULL;
    int i = 0;

    while (four->start->neighbours[i])
        four->start->neighbours[i++]->blacklist = 1;
    while (best_way) {
        four->start->neighbours[best_way->from]->blacklist = 0;
        best_way = best_way->next;
    }
    reset_all_way(four);
    road(0);
    insert_multiway(four, &useless);
    i = 0;
    while (four->start->neighbours[i])
        four->start->neighbours[i++]->blacklist = 0;
}

void brain(four_t *four, int diff)
{
    t_list *actual_way = NULL;
    t_list *best_way = NULL;
    int totallen = 0;
    int besttotal = 0;
    int old_badest = 0;

    int i = 0;
    while (i <= diff) {
        reset_all_way(four);
        totallen = insert_multiway(four, &actual_way);
        is_it_good(actual_way, &best_way, totallen, &besttotal);
        four->start->neighbours[old_badest]->blacklist = 0;
        old_badest = highest(actual_way);
        four->start->neighbours[old_badest]->blacklist = 1;
        i++;
        actual_way = NULL;
    }
    four->start->neighbours[old_badest]->blacklist = 0;
    set_best_way(four, best_way);
    insert_multiway(four, &actual_way);
}

char ***build_ways(four_t *four)
{
    int nbway = 0;
    char ***res = NULL;
    int totallen;
    t_list *actual_way = NULL;
    int i = -1;
    finish(0);
    road(1);
    four->direct_way = 0;
    while (four->start->neighbours[++i])
        if (four->start->neighbours[i]->pos == 2) {
            four->direct_way = 1;
            four->direct_name = four->start->neighbours[i]->name;
        }
    totallen = insert_multiway(four, &actual_way);
    int diff = struct_len(four->start->neighbours) - my_list_size(actual_way);
    if (diff > 0 + four->direct_way && totallen != 0)
        brain(four, diff);
    nbway = road(-1) - 1;
    res = output(four, four->start, nbway + four->direct_way);
    return (res);
}
