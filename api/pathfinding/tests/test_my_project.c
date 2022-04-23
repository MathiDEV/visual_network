/*
** EPITECH PROJECT, 2021
** tests
** File description:
** test_my_project.c
*/

#include "../include/my.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>

void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(my_strdup, test_basics, .init = redirect_all_std)
{
    cr_assert_str_eq(my_strdup("lol"), "lol");
}

Test(my_strlen, test_strlen, .init = redirect_all_std)
{
    cr_assert(my_strlen("DDDDDd") == 6);
    cr_assert(my_strlen(NULL) == -1);
}

Test(my_strcmp, test_cmp, .init = redirect_all_std)
{
    cr_assert(my_strcmp("DDDDDd", "DDDDDd") == 0);
    cr_assert(my_strcmp("s", "DDDDDd") > 0);
}

Test(my_getnbr, test_getnbr, .init = redirect_all_std)
{
    cr_assert(my_getnbr("-2147483648") == -1);
    cr_assert(my_getnbr("2147483647") == 2147483647);
}

Test(my_strdup, test_frees, .init = redirect_all_std)
{
    free_chars(my_split("coucou les amis", " "));
}