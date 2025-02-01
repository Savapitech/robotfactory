/*
** EPITECH PROJECT, 2023
** B-PSU-100-REN-1-1-myls-savinien.petitjean
** File description:
** lib/mu/u_strpop.c
*/

#include <stdlib.h>

#include "u_str.h"

char *u_strpop(char *str, int size)
{
    int l = u_strlen(str);
    char *strr = malloc((sizeof(char) * (l - size)) + 1);

    if (strr == NULL)
        return NULL;
    for (int i = 0; i < l - size; i++)
        strr[i] = str[i];
    strr[l - size] = '\0';
    return strr;
}
