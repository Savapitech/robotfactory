/*
** EPITECH PROJECT, 2025
** __
** File description:
** _
*/

#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>

#include "common.h"
#include "u_str.h"

static
bool get_valute_in_quote(char *buffer, buff_t *buff)
{
    for (; isblank(*buffer) && *buffer != '\0'; buffer++);
    if (*buffer != '"')
        return false;
    buffer++;
    buff->str = buffer;
    for (; *buffer != '"' && *buffer != '\0'; buffer++);
    if (*buffer != '"')
        return false;
    buff->sz = buffer - buff->str;
    return true;
}

buff_t get_metadata(char *buffer, char const *key, rf_t *rf)
{
    buff_t buff = { .str = NULL, 0 };
    size_t key_l = u_strlen(key);
    bool invalid = false;

    if (rf->lines_i > rf->lines_sz - 1)
        return buff;
    for (; *buffer != '.' && *buffer != '\0'; buffer++);
    if (u_strncmp(buffer, key, key_l) != 0)
        invalid = true;
    for (; !isblank(*buffer) && *buffer != '\0'; buffer++);
    if (!isblank(*buffer))
        return buff;
    if (!get_valute_in_quote(buffer, &buff))
        return (buff_t){ .str = NULL, 0 };
    if (invalid)
        return get_metadata(buffer + 1, key, rf);
    return buff;
}
