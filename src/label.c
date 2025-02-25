/*
** EPITECH PROJECT, 2025
** __
** File description:
** _
*/

#include <stdbool.h>
#include <stdlib.h>

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

static
size_t get_lbl_count(rf_t *rf)
{
    int lbl_size;
    size_t lbl_count = 0;

    for (size_t i = rf->lines_i; i < rf->lines_sz; i++) {
        lbl_size = get_lbl_sz(rf->lines[i]);
        if (lbl_size)
            lbl_count++;
    }
    return lbl_count;
}

bool parse_label_table(rf_t *rf)
{
    int lbl_size;
    size_t lbl_i = 0;

    rf->lbl_table_sz = get_lbl_count(rf);
    if (rf->lbl_table_sz < 1)
        return false;
    rf->lbl_table = malloc(sizeof *rf->lbl_table * rf->lbl_table_sz);
    if (rf->lbl_table == NULL)
        return false;
    for (size_t i = rf->lines_i; i < rf->lines_sz; i++) {
        lbl_size = get_lbl_sz(rf->lines[i]);
        if (lbl_size) {
            rf->lbl_table[lbl_i].name.str = rf->lines[i];
            rf->lbl_table[lbl_i].name.sz = lbl_size;
            U_DEBUG("Label [%lu] found [%d] [%.*s]\n", lbl_i, lbl_size,
                lbl_size, rf->lines[i]);
            lbl_i++;
        }
    }
    return true;
}
