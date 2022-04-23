/*
** EPITECH PROJECT, 2021
** B-CPE-200-LYN-2-1-lemin-valentin.dury
** File description:
** sort.c
*/

int n_worth_path(int n_ants, int n_paths, int *len)
{
    n_paths--;
    for (n_paths; n_paths > 0; n_paths--)
        if (n_ants / (n_paths + 1) + len[n_paths] <
        n_ants / n_paths + len[n_paths - 1])
            break;
    return (n_paths + 1);
}

void sort_by_len(int n_paths, int *len, char ***tables)
{
    int i = 0;
    char **temp;
    while (i < n_paths - 1) {
        if (len[i] > len[i + 1]) {
            len[i] ^= len[i + 1];
            len[i + 1] ^= len[i];
            len[i] ^= len[i + 1];
            temp = tables[i];
            tables[i] = tables[i + 1];
            tables[i + 1] = temp;
            i = 0;
            continue;
        }
        i++;
    }
}
