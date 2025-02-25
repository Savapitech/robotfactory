/*
** EPITECH PROJECT, 2025
** __
** File description:
** _
*/

#include <stdbool.h>

#include "compiler.h"
#include "common.h"
#include "debug.h"
#include "op.h"
#include "u_str.h"

static
size_t get_lbl_sz(char *line)
{
    size_t lbl_size = 0;

    lbl_size = u_strcspn(line, LABEL_CHAR);
    if (!lbl_size)
        return 0;
    if (u_strspn(line, LABEL_CHARS) != lbl_size)
        return 0;
    return lbl_size;
}

bool parse_label_table(rf_t *rf)
{
    int lbl_size;
    size_t lbl_count = 0;

    for (size_t i = rf->lines_i; i < rf->lines_sz; i++) {
        lbl_size = get_lbl_sz(rf->lines[i]);
        if (lbl_size) {
            U_DEBUG("Label found [%d] [%.*s]\n", lbl_size, lbl_size,
                rf->lines[i]);
        }
    }
    return true;
}
