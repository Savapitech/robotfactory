/*
** EPITECH PROJECT, 2025
** __
** File description:
** _
*/

#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

#include "common.h"
#include "debug.h"
#include "op.h"
#include "u_str.h"

int get_label_offset(rf_t *rf, char *label_name, int label_sz)
{
    if (!rf->lbl_table_sz)
        return -1;
    for (size_t i = 0; i < rf->lbl_table_sz; i++) {
        if (rf->lbl_table[i].name.sz != label_sz)
            continue;
        if (u_strncmp(rf->lbl_table[i].name.str, label_name,
            rf->lbl_table[i].name.sz) == 0)
            return rf->lbl_table[i].ins_pos;
    }
    return -1;
}

bool check_existing_lbl(rf_t *rf, char *label_name, int label_sz, size_t lbl_i)
{
    if (!rf->lbl_table_sz)
        return false;
    for (size_t i = 0; i < lbl_i; i++) {
        if (rf->lbl_table[i].name.sz != label_sz)
            continue;
        if (u_strncmp(rf->lbl_table[i].name.str, label_name,
            rf->lbl_table[i].name.sz) == 0)
            return true;
    }
    return false;
}

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
buff_t get_ins_name(char *line)
{
    buff_t buff = {NULL, 0};
    size_t len_instruction = 0;

    len_instruction = u_strccspn(line, " \t");
    if (!len_instruction)
        return (buff_t){.str = NULL};
    if (u_strspn(line, INSTRUCTION_CHARS) != len_instruction)
        return (buff_t){.str = NULL};
    buff.sz = len_instruction;
    buff.str = line;
    return buff;
}

static
void get_ref_count2(rf_t *rf, size_t i, int lbl_size)
{
    char *line = rf->lines[i];

    line += lbl_size + 1;
    SKIP_SPACES(line);
    if (!isalnum(*line))
        return;
    if (get_ins_name(line).sz)
        rf->ins_table_sz++;
}

static
void get_ref_count(rf_t *rf)
{
    int lbl_size;

    for (size_t i = rf->lines_i; i < rf->lines_sz; i++) {
        lbl_size = get_lbl_sz(rf->lines[i]);
        if (lbl_size) {
            rf->lbl_table_sz++;
            get_ref_count2(rf, i, lbl_size);
        } else
            rf->ins_table_sz++;
    }
}

static
ins_t get_ins(rf_t *rf, char *line)
{
    buff_t buff = { NULL, 0 };
    ins_t ins = { 0 };

    buff = get_ins_name(line);
    if (buff.str == NULL) {
        print_error(rf, "Invalid instruction.", false);
        return ins;
    }
    for (size_t i = 0; i < OP_TAB_SZ; i++) {
        if (u_strncmp(OP_TAB[i].mnemonique, buff.str, buff.sz) == 0) {
            ins.code = OP_TAB[i].code;
            ins.buff = buff;
            ins.has_cb = (OP_TAB[i].nbr_args > 1 || *OP_TAB[i].type != T_DIR);
            break;
        }
    }
    if (!ins.code)
        print_error(rf, "Invalid instruction.", false);
    return ins;
}

static
bool parse_line2(rf_t *rf, int lbl_size, char *line, size_t *ins_i)
{
    if (!rf->ins_table_sz)
        return true;
    if (lbl_size)
        line += lbl_size + 1;
    SKIP_SPACES(line);
    if (!isalnum(*line))
        return true;
    rf->ins_table[*ins_i] = get_ins(rf, line);
    rf->ins_table[*ins_i].size = 1;
    rf->ins_table[*ins_i].ins_i = *ins_i;
    if (rf->ins_table[*ins_i].buff.str == NULL)
        return false;
    U_DEBUG("Ins found [%.*s] code [%d] line i [%lu] ins i [%lu]\n",
        rf->ins_table[*ins_i].buff.sz, rf->ins_table[*ins_i].buff.str,
        rf->ins_table[*ins_i].code, rf->lines_i, *ins_i);
    *ins_i += 1;
    return true;
}

static
bool parse_line(rf_t *rf, size_t *lbl_i, size_t *ins_i)
{
    int lbl_size = 0;
    char *line = rf->lines[rf->lines_i];

    if (rf->lbl_table_sz)
        lbl_size = get_lbl_sz(line);
    if (lbl_size) {
        if (*lbl_i && check_existing_lbl(rf, line, lbl_size, *lbl_i))
            return (print_error(rf, "Multiple definition of the same label.",
                false), false);
        rf->lbl_table[*lbl_i].name.str = line;
        rf->lbl_table[*lbl_i].name.sz = lbl_size;
        rf->lbl_table[*lbl_i].ins_pos = *ins_i;
        U_DEBUG("Label found [%.*s] [%lu] line i [%lu]\n", lbl_size, line,
            *ins_i, rf->lines_i);
        *lbl_i += 1;
    }
    return parse_line2(rf, lbl_size, line, ins_i);
}

bool parse_label_table(rf_t *rf)
{
    size_t lbl_i = 0;
    size_t ins_i = 0;

    get_ref_count(rf);
    if (rf->lbl_table_sz) {
        rf->lbl_table = malloc(sizeof *rf->lbl_table * rf->lbl_table_sz);
        if (rf->lbl_table == NULL)
            return false;
    }
    if (rf->ins_table_sz) {
        rf->ins_table = malloc(sizeof *rf->ins_table * rf->ins_table_sz);
        if (rf->ins_table == NULL)
            return false;
    }
    for (; rf->lines_i < rf->lines_sz; rf->lines_i++)
        if (!parse_line(rf, &lbl_i, &ins_i))
            return false;
    U_DEBUG("Found [%lu] label%s, [%lu] ins.\n", rf->lbl_table_sz,
        rf->lbl_table_sz > 1 ? "s" : "", rf->ins_table_sz);
    return true;
}
