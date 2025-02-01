/*
** EPITECH PROJECT, 2024
** CPoolDay07
** File description:
** ./u_putstr.c
*/

#include <unistd.h>

#include "u_str.h"

int u_puterr(char const *str)
{
    return write(STDERR_FILENO, str, u_strlen(str));
}
