/*
** EPITECH PROJECT, 2022
** create graph
** File description:
** create an array of neighbours
*/

#include "my.h"

room_t *get_room_by_name(four_t *hill, char *name)
{
    room_t *room = hill->rooms;
    while (room != NULL) {
        if (my_strcmp(room->name, name) == 0)
            return (room);
        room = room->next;
    }
    return (NULL);
}

int set_neighbours(four_t *hill)
{
    room_t *room = NULL;
    links_t *way = NULL;

    for (room = hill->rooms; room != NULL; room = room->next) {
        room->neighbours =
        malloc(sizeof(room_t *) * (room->links_nb + room->neighbours_nb + 1));
        if (room->neighbours == NULL)
            return (84);
        room->neighbours[room->links_nb + room->neighbours_nb] = NULL;
    }
    for (room = hill->rooms; room != NULL; room = room->next) {
        for (way = room->links; way != NULL && way->go_to != NULL;
            way = way->next) {
            room->neighbours[room->current_neighbour] = way->go_to;
            room->current_neighbour++;
            way->go_to->neighbours[way->go_to->current_neighbour] = room;
            way->go_to->current_neighbour++;
        }
    }
    return (0);
}

int iterate_links(room_t *room, four_t *hill)
{
    int len = 0;
    for (links_t *way = room->links; way != NULL; way = way->next) {
        way->go_to = get_room_by_name(hill, way->name);
        if (way->go_to == NULL) {
            room->links_nb = len;
            return (84);
        }
        way->go_to->neighbours_nb += 1;
        len++;
    }
    room->links_nb = len;
}

int create_graph(four_t *hill)
{
    room_t *room = hill->rooms;

    while (room != NULL) {
        if (iterate_links(room, hill) == 84)
            break;
        room = room->next;
    }
    return (set_neighbours(hill));
}
