/*
** EPITECH PROJECT, 2024
** CPoolDay07
** File description:
** ./u_putchar.c
*/

#include <unistd.h>

int u_putchar(char a)
{
    return (write(1, &a, 1) - 1);
}
