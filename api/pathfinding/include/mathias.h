/*
** EPITECH PROJECT, 2022
** lemin
** File description:
** mathias
*/

#ifndef _MATHIAS_H_
    #define _MATHIAS_H_
    void print_moves(int n_ants, char ***paths);
    int triple_strlen(char ***table);
    int double_strlen(char **table);
    int my_putstr(char *str);
    void my_putnbr(int nb);
    void my_putchar(char c);
    void my_put_nbr(int nbr);
    void sort_by_len(int n_paths, int *len, char ***tables);
    int n_worth_path(int n_ants, int n_paths, int *len);
    typedef struct printer_t {
        int n_paths;
        int n_ants;
        int ants_in_hill;
        int arrived_ants;
        int turn_first_step;
        int step_id;
        int removed;
        int ant_id;
        int this_begin;
    } printer;
#endif
