/*
** EPITECH PROJECT, 2025
** __
** File description:
** _
*/

#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>

#include "u_str.h"

bool u_strnum(char *strp, int *n, size_t sz)
{
    char *s = strp;
    int num = 0;
    bool negative = (*s == '-');

    if (negative)
        s++;
    for (size_t i = 0; i < sz; i++)
        if (!isdigit(strp[i]) && !isblank(strp[i]) && strp[i] != ','
            && strp[i] != '-' && strp[i] != '\0')
            return false;
    for (; isdigit(*s); s++)
        num = (10 * num) - (*s - '0');
    *n = (negative) ? num : - num;
    return true;
}
