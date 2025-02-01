/*
** EPITECH PROJECT, 2024
** CPoolDay07
** File description:
** ./u_putstr.c
*/

#include "u_write.h"

int u_putstr(char const *str)
{
    for (int i = 0; str[i] != '\0'; i++)
        u_putchar(str[i]);
    return (0);
}
