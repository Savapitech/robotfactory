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
void get_ref_count(rf_t *rf)
{
    int lbl_size;

    for (size_t i = rf->lines_i; i < rf->lines_sz; i++) {
        lbl_size = get_lbl_sz(rf->lines[i]);
        if (lbl_size)
            rf->lbl_table_sz++;
        else
            rf->ins_table_sz++;
    }
}

static
buff_t get_ins_name(char *line)
{
    buff_t buff = {NULL, 0};
    size_t len_instruction = 0;

    len_instruction = u_strcspn(line, INSTRUCTION_CHAR);
    if (!len_instruction)
        return (buff_t){.str = NULL};
    if (u_strspn(line, INSTRUCTION_CHARS) != len_instruction)
        return (buff_t){.str = NULL};
    buff.sz = len_instruction;
    buff.str = line;
    return buff;
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
bool parse_line(rf_t *rf, size_t i, size_t *lbl_i, size_t *ins_i)
{
    int lbl_size = 0;

    if (rf->lbl_table_sz)
        lbl_size = get_lbl_sz(rf->lines[i]);
    if (lbl_size) {
        rf->lbl_table[*lbl_i].name.str = rf->lines[i];
        rf->lbl_table[*lbl_i].name.sz = lbl_size;
        rf->lbl_table[*lbl_i].ins_pos = *ins_i;
        U_DEBUG("Label found [%.*s] [%lu]\n", lbl_size, rf->lines[i], *ins_i);
        *lbl_i += 1;
        return true;
    }
    if (!rf->ins_table_sz)
        return true;
    rf->ins_table[*ins_i] = get_ins(rf, rf->lines[i]);
    if (rf->ins_table[*ins_i].buff.str == NULL)
        return false;
    U_DEBUG("Ins found code [%d]\n", rf->ins_table[*ins_i].code);
    *ins_i += 1;
    return true;
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
    for (size_t i = rf->lines_i; i < rf->lines_sz; i++)
        if (!parse_line(rf, i, &lbl_i, &ins_i))
            return false;
    return true;
}
