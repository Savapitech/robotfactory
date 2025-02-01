/*
** EPITECH PROJECT, 2024
** CPoolDay08
** File description:
** ./lin/my/u_show_word_array.c
*/

#include "u_write.h"

int u_show_word_array(char *const *tab)
{
    for (int i = 0; tab[i] != 0; i++) {
        u_putstr(tab[i]);
        u_putchar('\n');
    }
    return 0;
}
