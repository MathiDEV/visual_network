/*
** EPITECH PROJECT, 2021
** my.h
** File description:
** oui
*/

#ifndef _MY_H_
    #define _MY_H_
    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include "valentin.h"
    #include "mathias.h"
    #include "solver.h"
    typedef struct file_s {
        char *name;
        struct file_s *next;
    } file_t;
    typedef struct links_s {
        char *name;
        struct links_s *next;
        struct room_s *go_to;
    } links_t;
    typedef struct room_s {
        char *name;
        int pos;
        int cost;
        int visited;
        int way;
        int blacklist;
        int links_nb;
        int neighbours_nb;
        int current_neighbour;
        struct room_s *start;
        struct room_s *next;
        struct room_s **neighbours;
        links_t *links;
    } room_t;
    typedef struct four_s {
        int nb_four;
        struct room_s *start;
        struct room_s *end;
        char **map;
        int direct_way;
        char *direct_name;
        int piv;
        int nb_v;
        int b_err;
        room_t *rooms;
    } four_t;
    typedef struct s_list {
        int data;
        int from;
        int g_cost;
        struct room_s *me;
        struct s_list *before;
        struct s_list *next;
        struct s_list *prev;
    } t_list;

    //autocomplete:start
    int highest(t_list *before);
    void is_it_good(t_list *ac, t_list **b, int ten, int *maxlen);
    int insert_multiway(four_t *four, t_list **actual_way);
    int find_actual_pos(int id_way, room_t *room);
    int struct_len(room_t **room);
    int size(int piece);
    int lem_in(void);
    int my_strcmp(char *s1, char *s2);
    int my_strlen(char *str);
    char *my_strdup(char *str);
    int my_getnbr(char *str);
    void free_chars(char **r);
    room_t *get_room_by_name(four_t *hill, char *name);
    int set_neighbours(four_t *hill);
    int create_graph(four_t *hill);
    int in_charset(char c, char *charset);
    char **my_split(char *str, char *charset);
    four_t *get_fourmilliere(void);
    room_t *create_elem_room(char *name, int *pos);
    void push_front_room(room_t **room, char *name, int *pos, four_t *four);
    int pushback_rooms(room_t **b_l, char *name, int *pos, four_t *four);
    int pushback_links(links_t **b_l, char *data);
    int push_liaisons(room_t *room, char *name, char *name2);
    char *trim_hashtag(char *str);
    int has_dash(char *str);
    char *get_name(char *str, char cep);
    int col_len(char **res);
    int check_line(char *s);
    file_t *create_elem_file(char *name);
    char *read_standard(void);
    file_t *fourmilliere(int *len);
    int triple_strlen(char ***table);
    int double_strlen(char **table);
    void my_put_nbr(int nbr);
    void my_putchar(char c);
    int my_putstr(char *str);
    void my_putnbr(int nb);
    int get_ant_out(int n, int *ants, int ants_in_hill, int n_ants);
    void print_ant_move(int ant_id, char *room_name, int last);
    void ant_loop(printer *dt, int *ants, char ***paths, int *path_len);
    void print_moves(int n_ants, char ***paths);
    int finish(int piece);
    int road(int piece);
    t_list *add_in_queu(t_list *openlist, room_t *room, t_list *l, t_list *f);
    void print_way(t_list *last);
    t_list *open_all(t_list *openlist, room_t *room, t_list *l, t_list *f);
    void reset_list(t_list *list, t_list *list2);
    int bfs(room_t *room);
    t_list *my_creat_elem(int data, t_list *prev);
    t_list *my_list_push_back(t_list **begin_list, int data, t_list *last);
    int my_list_size(t_list const *begin);
    void my_list_push_front(t_list **begin_list, int data);
    t_list *set_last(t_list *list);
    void delete_node(t_list **list, t_list **truelist);
    t_list *my_list_dup(t_list *list);
    void my_list_push_front_reset(t_list **begin_list, t_list *node);
    char ***build_ways(four_t *four);
    char **fill_tab(char **res, int id_way, room_t *start, int len_pos);
    char ***output(four_t *four, room_t *room, int nbway);
    void redirect_all_std(void);
    //autocomplete:end
    #include "joshua.h"
#endif
