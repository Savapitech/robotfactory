/*
** EPITECH PROJECT, 2025
** __
** File description:
** _
*/

#include "u_str.h"

int u_strcspn(char const *str, char c)
{
    char const *old_str = str;

    for (; *str != '\0'; str++)
        if (*str == c)
            return str - old_str;
    return 0;
}

int u_strcrspn(char const *str, char c)
{
    size_t len = u_strlen(str);
    char const *p = str + len;

    if (!len)
        return -1;
    for (; p != str; p--)
        if (*p == c)
            return p - str;
    return 0;
}
