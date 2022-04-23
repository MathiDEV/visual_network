/*
** EPITECH PROJECT, 2021
** push_swap
** File description:
** fct_list2
*/

#include "my.h"

t_list *set_last(t_list *list)
{
    while (list->next)
        list = list->next;
    return (list);
}

void delete_node(t_list **list, t_list **truelist)
{
    t_list *prev = *list;

    if (!(*truelist)->next) {
        *truelist = NULL;
        return;
    }
    if ((*list)->prev) {
        prev = (*list)->prev;
    } else {
        *truelist = (*truelist)->next;
        (*truelist)->prev = NULL;
        return;
    }
    if ((*list)->next) {
        prev->next = (*list)->next;
        prev->next->prev = prev;
    } else
        prev->next = NULL;
    *list = prev;
}

t_list *my_list_dup(t_list *list)
{
    t_list *res = NULL;
    t_list *last = NULL;
    while (list) {
        last = my_list_push_back(&res, list->data, last);
        list = list->next;
    }
    return (res);
}

void my_list_push_front_reset(t_list **begin_list, t_list *node)
{
    t_list *list = node;

    if (!*begin_list) {
        node->prev = NULL;
        node->next = NULL;
        *begin_list = node;
        return;
    }
    list->next = *begin_list;
    (*begin_list)->prev = list;
    *begin_list = list;
}
