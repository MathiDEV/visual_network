/*
** EPITECH PROJECT, 2022
** lemin
** File description:
** read_standard
*/

#include "../../include/my.h"

file_t *create_elem_file(char *name)
{
    file_t *new = malloc(sizeof(file_t));

    new->name = name;
    new->next = NULL;
    return (new);
}

char *read_standard(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    read = getline(&line, &len, stdin);
    if (read == -1)
        return (NULL);
    return (line);
}

file_t *fourmilliere(int *len)
{
    file_t *file = malloc(sizeof(file_t));
    file_t *tmp = file;
    int siu = 0;
    char *line = NULL;
    int ite = -1;

    int prev = 0;
    while ((line = read_standard()) != NULL) {
        if (line[0] && line[0] == '#' && line[1] && line[1] != '#')
            continue;
        if ((line[0] && line[0] == '#' && line[1] && line[1] == '#') &&
        (my_strcmp(line, "##start\n") != 0 && my_strcmp(line, "##end\n") != 0))
            continue;
        file->next = create_elem_file(line);
        file = file->next;
        (*len)++;
    }
    if (*len == 0)
        return (NULL);
    return (tmp->next);
}

char **get_standard(int st, int end, four_t *four, int len)
{
    int i = -1;
    char **res = NULL;
    file_t *file = fourmilliere(&len);

    res = malloc(sizeof(char *) * (len + 1));
    for (; file; file = file->next) {
        if (i != -1 && !check_line(file->name))
            four->nb_v = four->nb_v == -1 ? i + 1 : four->nb_v;
        if (my_strcmp(file->name, "##start\n") == 0)
            st++;
        if (my_strcmp(file->name, "##end\n") == 0)
            end++;
        res[++i] = file->name;
    }
    if (st != 1 || end != 1)
        four->b_err = 1;
    res[++i] = NULL;
    four->nb_v = four->nb_v == -1 ? i : four->nb_v;
    return (res);
}
