/*
** EPITECH PROJECT, 2021
** push_swap
** File description:
** No file there , just an epitech header example
*/

#include "my.h"

t_list *my_creat_elem(int data, t_list *prev)
{
    t_list *list;
    list = malloc(sizeof(t_list));
    list->data = data;
    list->prev = prev;
    list->next = NULL;
    return (list);
}

t_list *my_list_push_back(t_list **begin_list, int data, t_list *last)
{
    t_list *list = *begin_list;

    if (!list) {
        *begin_list = my_creat_elem(data, NULL);
        return (*begin_list);
    }
    last->next = my_creat_elem(data, last);
    return (last->next);
}

int my_list_size(t_list const *begin)
{
    int i = 0;

    while (begin) {
        i++;
        begin = begin->next;
    }
    return (i);
}

void my_list_push_front(t_list **begin_list, int data)
{
    t_list *list;

    if (!*begin_list) {
        *begin_list = my_creat_elem(data, NULL);
        return;
    }
    list = my_creat_elem(data, NULL);
    list->data = data;
    list->next = *begin_list;
    (*begin_list)->prev = list;
    *begin_list = list;
}
