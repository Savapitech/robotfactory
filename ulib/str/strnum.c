/*
** EPITECH PROJECT, 2025
** __
** File description:
** _
*/

#include <ctype.h>
#include <stdbool.h>

bool u_strnum(char *strp, int *n)
{
    char *s = strp;
    int num = 0;
    bool negative = (*s == '-');

    if (negative)
        s++;
    for (; isdigit(*s); s++)
        num = (10 * num) - (*s - '0');
    *n = (negative) ? num : - num;
    return true;
}
