/*
** EPITECH PROJECT, 2021
** my.h
** File description:
** oui
*/

#ifndef _JOSHUA_H_
    #define _JOSHUA_H_
    int my_strcmp(char *s1, char *s2);
    int my_strlen(char *str);
    char *my_strdup(char *str);
    char **get_standard(int st, int end, four_t *four, int len);
    int my_getnbr(char *str);
    char *get_name(char *str, char cep);
    int has_dash(char *str);
    char **my_split(char *str, char *charset);
    int check_line(char *s);
    void free_chars(char **r);
    void pushback_rooms_side(int ttmp, four_t *four, room_t *new);
    int pushback_rooms(room_t **b_l, char *name, int *pos, four_t *four);
    char *trim_hashtag(char *str);
#endif /* _JOSHUA_H_ */
