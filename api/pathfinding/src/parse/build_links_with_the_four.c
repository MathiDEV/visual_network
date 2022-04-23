/*
** EPITECH PROJECT, 2022
** parse
** File description:
** build_four_utils
*/

#include "../../include/my.h"

room_t *create_elem_room(char *name, int *pos)
{
    room_t *new = malloc(sizeof(room_t));

    new->name = name;
    new->pos = *pos;
    new->way = 0;
    new->visited = 0;
    new->blacklist = 0;
    new->links = NULL;
    new->neighbours = NULL;
    new->next = NULL;
    new->current_neighbour = 0;
    new->links_nb = 0;
    new->neighbours_nb = 0;
    *pos = 0;
    return (new);
}

void push_front_room(room_t **room, char *name, int *pos, four_t *four)
{
    int tmp = *pos;
    room_t *new = create_elem_room(name, pos);

    new->name = name;
    new->next = *room;
    *room = new;
    if (tmp == 1)
        four->start = new;
}

int pushback_rooms(room_t **b_l, char *name, int *pos, four_t *four)
{
    room_t *tmp;
    int ttmp = *pos;
    room_t *new = create_elem_room(name, pos);

    pushback_rooms_side(ttmp, four, new);
    if (!(*b_l)) {
        *b_l = new;
        return 1;
    }
    tmp = *b_l;
    while (tmp->next) {
        if (my_strcmp(tmp->name, name) == 0)
            return 0;
        tmp = tmp->next;
    }
    if (my_strcmp(tmp->name, name) == 0)
        return 0;
    tmp->next = new;
    return 1;
}

int pushback_links(links_t **b_l, char *data)
{
    links_t *new = malloc(sizeof(links_t));
    links_t *tmp;

    new->name = data;
    new->next = NULL;
    new->go_to = NULL;
    if (!(*b_l)) {
        *b_l = new;
        return 1;
    }
    tmp = *b_l;
    while (tmp->next) {
        if (my_strcmp(tmp->name, data) == 0)
            return 0;
        tmp = tmp->next;
    }
    tmp->next = new;
    return 1;
}

int push_liaisons(room_t *room, char *name, char *name2)
{
    room_t *tmp = room;
    int n1 = 0;

    if (my_strcmp(name, name2) == 0)
        return 1;
    for (; tmp != NULL; tmp = tmp->next) {
        if (!(my_strcmp(tmp->name, name))) {
            pushback_links(&tmp->links, name2);
            n1++;
        }
    }
    return ((n1 == 1));
}
