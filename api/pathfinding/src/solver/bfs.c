/*
** EPITECH PROJECT, 2022
** lemin
** File description:
** parse_standard
*/

#include "my.h"

t_list *open_all(t_list *openlist, room_t *room, t_list *last, t_list *from)
{
    int i = 0;
    while (room->neighbours[i]) {
        if (room->neighbours[i]->visited == 0 &&
        room->neighbours[i]->way == 0 && room->neighbours[i]->blacklist != 1)
            last = add_in_queu(openlist, room->neighbours[i], last, from);
        if (room->neighbours[i]->pos == 2 && room->pos != 1) {
            print_way(from);
            room->visited = 0;
            size(from->data + 2);
            finish(1);
            return (0);
        }
        i++;
    }
    return (last);
}

void reset_list(t_list *list, t_list *list2)
{
    while (list) {
        list->me->visited = 0;
        list = list->next;
    }
    while (list2) {
        list2->me->visited = 0;
        list2 = list2->next;
    }
}

void sub_bfs(t_list **openlist, t_list **closed, t_list **from, room_t **room)
{
    *openlist = (*openlist)->next;
    my_list_push_front_reset(closed, (*openlist)->prev);
    *from = *openlist;
    *room = (*openlist)->me;
}

int bfs(room_t *room)
{
    int still = 1;
    t_list *openlist = my_creat_elem(0, NULL);
    t_list *closed = NULL;
    t_list *last = openlist;
    t_list *from = NULL;
    room->visited = 1;
    openlist->me = room;
    while (openlist) {
        last = open_all(openlist, room, last, from);
        if (finish(-1)) {
            reset_list(closed, openlist);
            return (1);
        }
        if (!openlist->next) {
            reset_list(closed, openlist);
            return (0);
        }
        sub_bfs(&openlist, &closed, &from, &room);
    }
    return (0);
}
