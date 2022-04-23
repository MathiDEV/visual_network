/*
** EPITECH PROJECT, 2022
** lemin
** File description:
** parse_utils
*/

#include "../../include/my.h"

char *trim_hashtag(char *str)
{
    int i = 0;

    if (!my_strcmp(str, "##start\n") || !my_strcmp(str, "##end\n"))
        return (str);
    for (; str[i]; i++) {
        if (str[i] == '#')
            break;
    }
    while (--i > 0 && (str[i] == ' ' || str[i] == '#'))
        str[i] = '\0';
    return (str);
}

int has_dash(char *str)
{
    int i = -1;
    int nb = 0;

    while (str[++i])
        if (str[i] == '-')
            nb++;
    return (nb);
}

char *get_name(char *str, char cep)
{
    int i = 0;
    char *name = NULL;

    while (str[i] && str[i] != cep)
        i++;
    name = malloc(sizeof(char) * (i + 1));
    i = 0;
    while (str[i] && str[i] != cep) {
        name[i] = str[i];
        i++;
    }
    name[i] = '\0';
    return (name);
}

int col_len(char **res)
{
    int i = 0;

    while (res[i])
        i++;
    return (i);
}

int check_line(char *s)
{
    char **res = my_split(trim_hashtag(s), " ");
    int len = col_len(res);

    if (s[0] == '#')
        return 1;
    if (len != 3 && len != 1)
        return (0);
    if (len == 1) {
        if (has_dash(s) != 1)
            return 0;
        return 1;
    }
    for (int i = 0; res[1] && res[1][i]; i++)
        if (!(res[1][i] >= '0' && res[1][i] <= '9')) {
            return (0);
        }
    for (int i = 0; res[2] && res[2][i] && res[2][i] != '\n'; i++)
        if (!(res[2][i] >= '0' && res[2][i] <= '9'))
            return (0);
    return 1;
}
