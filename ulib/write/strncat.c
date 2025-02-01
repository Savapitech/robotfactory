/*
** EPITECH PROJECT, 2024
** CPoolDay07
** File description:
** ./u_strncat.c
*/

#include "u_str.h"

char *u_strncat(char *dest, char const *src, int nb)
{
    int i = 0;
    int len = u_strlen(dest);

    while (src[i] != '\0' && i < nb) {
        dest[i + len] = src[i];
        i++;
    }
    dest[i + len] = '\0';
    return dest;
}
