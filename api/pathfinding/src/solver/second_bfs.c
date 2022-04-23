/*
** EPITECH PROJECT, 2022
** lemin
** File description:
** parse_standard
*/

#include "my.h"

int size(int piece)
{
    int static actual;

    if (piece != -1)
        actual = piece;
    return (actual);
}

int finish(int piece)
{
    int static actual;

    if (piece != -1)
        actual = piece;
    return (actual);
}

int road(int piece)
{
    int static actual;

    if (piece != -1)
        actual = piece;
    return (actual);
}

t_list *add_in_queu(t_list *openlist, room_t *room, t_list *last, t_list *from)
{
    room->visited = 1;
    if (from)
        last = my_list_push_back(&openlist, from->data + 1, last);
    else
        last = my_list_push_back(&openlist, 0, last);
    last->before = from;
    last->me = room;
    return (last);
}

void print_way(t_list *last)
{
    while (last) {
        last->me->way = road(-1);
        last = last->before;
    }
}
