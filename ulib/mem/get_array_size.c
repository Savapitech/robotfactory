/*
** EPITECH PROJECT, 2024
** B-CPE-100-REN-1-1-cpoolday10-savinien.petitjean
** File description:
** ./do-op/u_do-op.c
*/

int u_get_array_size(char **tab)
{
    int i = 0;

    for (; tab[i] != 0; i++);
    return i;
}
