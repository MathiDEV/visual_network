/*
** EPITECH PROJECT, 2022
** lemin
** File description:
** parse_standard
*/

#include "../../include/my.h"

void pushback_rooms_side(int ttmp, four_t *four, room_t *new)
{
    if (ttmp == 1)
        four->start = new;
    if (ttmp == 2)
        four->end = new;
}

four_t *prechauffer_four(void)
{
    four_t *four = malloc(sizeof(four_t));

    four->start = NULL;
    four->end = NULL;
    four->rooms = NULL;
    four->b_err = 0;
    four->nb_v = -1;
    return four;
}

int get_fourmilliere_up(four_t *fu, char **res, int pos)
{
    int i = 0;
    for (i = 0; ++i < fu->nb_v && res[i] && !has_dash(res[i]); i) {
        if (my_strcmp(res[i], "##start\n") == 0) {
            pos = 1;
            continue;
        }
        if (my_strcmp(res[i], "##end\n") == 0) {
            pos = 2;
            continue;
        }
        if (!(pushback_rooms(&fu->rooms, get_name(res[i], ' '), &pos, fu))) {
            fu->b_err = 1;
            return 0;
        }
    }
    fu->piv = i;
    return 1;
}

int get_fourmilliere_dw(room_t *rooms, char **res, four_t *four)
{
    int i = -1;
    int lk = 0;
    char *tmp1;
    room_t *tmp = rooms;

    while (++i < four->nb_v && res[i]) {
        if (!has_dash(res[i]))
            continue;
        else
            lk++;
        tmp1 = get_name(res[i], '-');
        if (!(push_liaisons(
            tmp, tmp1, get_name(&res[i][my_strlen(tmp1) + 1], '\n'))))
            return 0;
    }
    return lk != 0;
}

four_t *get_fourmilliere(void)
{
    four_t *four = prechauffer_four();
    char **res = get_standard(0, 0, four, 0);
    int pos = 0;
    four->map = res;

    four->nb_four = res[0] ? my_getnbr(res[0]) : my_getnbr("Nekfeuj");
    if (four->nb_four < 0) {
        four->b_err = 1;
        return four;
    }
    if (four->b_err || !get_fourmilliere_up(four, res, pos))
        return (four);
    if (four->start == NULL || four->end == NULL)
        four->b_err = 1;
    if (four->b_err || !get_fourmilliere_dw(four->rooms, res, four))
        return four;
    return four;
}
