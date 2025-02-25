/*
** EPITECH PROJECT, 2025
** __
** File description:
** _
*/

#include <stddef.h>

char *u_strchr(const char *s, char c)
{
    for (char *p = (char *)s; *p != '\0'; p++)
        if (*p == c)
            return p;
    return NULL;
}

size_t u_strspn(const char *s, const char *accept)
{
    const char *p = s;

    for (; *p != '\0' && u_strchr(accept, *p) != NULL; p++);
    return p - s;
}

size_t u_strccspn(const char *s, const char *reject)
{
    const char *p = s;

    for (; *p != '\0' && u_strchr(reject, *p) == NULL; p++);
    return p - s;
}
