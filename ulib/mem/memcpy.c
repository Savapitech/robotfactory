/*
** EPITECH PROJECT, 2024
** CPoolDay08
** File description:
** ./u_realloc.c
*/

#include <stddef.h>
#include <stdint.h>

void *u_memcpy(void *dest, void const *src, size_t n)
{
    uint8_t const *srcp = src;

    if (dest == NULL || src == NULL)
        return NULL;
    for (uint8_t *destp = dest; n != 0; n--) {
        *destp = *srcp;
        destp++;
        srcp++;
    }
    return dest;
}
