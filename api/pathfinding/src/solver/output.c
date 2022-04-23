/*
** EPITECH PROJECT, 2022
** lemin
** File description:
** parse_standard
*/

#include "../../include/my.h"

int road_len(room_t *start, int nb_way)
{
    int i = 0;
    int len = 0;

    while (start->pos != 2) {
        while (
        start->neighbours[i]->way != nb_way && start->neighbours[i]->pos != 2)
            i++;
        start->way = -1;
        start = start->neighbours[i];
        i = 0;
        len++;
    }
    return (len + 1);
}

char **fill_tab(char **res, int id_way, room_t *start, int len_pos)
{
    int i = 0;
    int len = 0;
    int j = 0;

    res = malloc((len_pos + 1) * sizeof(char *));
    while (start->pos != 2) {
        while (
        start->neighbours[i]->way != -1 && start->neighbours[i]->pos != 2)
            i++;
        start->way = 0;
        res[j] = start->name;
        start = start->neighbours[i];
        i = 0;
        j++;
    }
    res[j++] = my_strdup(start->name);
    res[j] = 0;
    return (res);
}

char ***output(four_t *four, room_t *room, int nbway)
{
    char ***res = malloc((nbway + 1) * sizeof(char **));
    int len_pos = 0;
    int i = -1;
    int id_way = 0;
    int po = 0;
    if (nbway == 0)
        return (0);
    if (four->direct_way) {
        res[po] = malloc(sizeof(char *));
        res[po++][0] = four->direct_name;
    }
    while (room->neighbours[++i])
        if (room->neighbours[i]->way != 0) {
            id_way = room->neighbours[i]->way;
            len_pos = road_len(room->neighbours[i], id_way);
            res[po] = fill_tab(res[po], id_way, room->neighbours[i], len_pos);
            po++;
        }
    res[po] = 0;
    return (res);
}
