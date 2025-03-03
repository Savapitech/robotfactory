/*
** EPITECH PROJECT, 2025
** __
** File description:
** _
*/

#include <stdbool.h>
#include <unistd.h>

#include "common.h"
#include "compiler.h"
#include "debug.h"
#include "op.h"
#include "u_mem.h"

static
char get_arg_type(char const *arg)
{
    char type;
    size_t idx;

    if (*arg == 'r')
        return T_REG;
    type = (*arg == DIRECT_CHAR) ? T_DIR : T_IND;
    idx = (type & T_DIR) != 0;
    if (arg[idx] == LABEL_CHAR)
        type |= T_LAB;
    return type;
}

static
bool write_value(rf_t *rf, arg_t *arg, ins_t *ins)
{
    char *fbuff_ptr = rf->final_buff.str + rf->final_buff.sz;

    U_DEBUG("Writing [%lu] byte%s value [%d]\n", arg->size,
        (arg->size > 1 ? "s" : ""), arg->dir);
    if (arg->size == sizeof(char)) {
        u_memcpy(fbuff_ptr, &arg->reg, sizeof(arg->reg));
        rf->final_buff.sz++;
    } else if (arg->size == sizeof(short)) {
        arg->idx = (short)__builtin_bswap16((unsigned short)arg->dir);
        u_memcpy(fbuff_ptr, &arg->idx, sizeof arg->idx);
        rf->final_buff.sz += sizeof arg->idx;
    } else {
        arg->dir = (int)__builtin_bswap32((unsigned int)arg->dir);
        u_memcpy(fbuff_ptr, &arg->dir, sizeof arg->dir);
        rf->final_buff.sz += sizeof arg->dir;
    }
    rf->prog_sz += arg->size;
    ins->size += arg->size;
    return true;
}

static
bool process_label(rf_t *rf, arg_t *arg, ins_t *ins)
{
    char *arg_buff = arg->buff->str;
    size_t del_nonalpha = u_strccspn(arg_buff, LABEL_CHARS);
    size_t arg_len = u_strccspn(arg_buff + del_nonalpha, ", \t");
    int ins_pos;

    if (arg_buff > arg->buff->str + arg->buff->sz)
        return false;
    ins_pos = get_label_offset(rf, arg_buff + del_nonalpha, arg_len);
    if (ins_pos == -1)
        return (print_error(rf, "Undefined label.", false), false);
    arg->idx = 0;
    write_value(rf, arg, ins);
    ins->lbl_ptr = rf->final_buff.str + rf->final_buff.sz - 2;
    ins->lbl_ins_pos = ins_pos;
    return true;
}

static
bool process_arg_dir_idx(rf_t *rf, arg_t *arg, char type, ins_t *ins)
{
    arg->size = (!(type & T_DIR) || IS_IDX(ins->code))
        ? sizeof(short) : sizeof(int);
    if (type & T_DIR && !(type & T_LAB)) {
        arg->buff->str++;
        if (!u_strnum(arg->buff->str, &arg->dir))
            return false;
        write_value(rf, arg, ins);
    }
    if (type & T_IND) {
        if (!u_strnum(arg->buff->str, &arg->dir))
            return false;
        arg->idx = arg->dir;
        arg->size = 2;
        write_value(rf, arg, ins);
    }
    if (type & T_LAB)
        if (!process_label(rf, arg, ins))
            return false;
    return true;
}

static
bool process_arg(rf_t *rf, buff_t *arg_buffp, ins_t *ins, size_t arg_i)
{
    arg_t arg = { .buff = arg_buffp, .size = sizeof(char) };
    char type = get_arg_type(arg.buff->str);

    if (!(OP_TAB[ins->code - 1].type[arg_i] & type))
        return (print_error(rf, "The argument given to the instruction is "
            "invalid.", false), false);
    ins->cb = (ins->cb << 2) | CALC_CB(type);
    if (type & T_REG) {
        arg.buff->str++;
        if (!u_strnum(arg.buff->str, &arg.dir) || !arg.dir || arg.dir >
            REG_NUMBER)
            return (print_error(rf, "Invalid register number.", false), false);
        write_value(rf, &arg, ins);
    }
    if (type & T_DIR) {
        if (*(arg.buff->str + 1) != ':' && !isdigit(*(arg.buff->str + 1)))
            return (print_error(rf, "The argument given to the instruction is "
                "invalid.", false), false);
    }
    return process_arg_dir_idx(rf, &arg, type, ins);
}

static
int get_args(rf_t *rf, op_t const *op, ins_t *ins, size_t ins_idx)
{
    char *ins_arg_str = ins->buff.str + ins->buff.sz + 1;
    buff_t arg_buff;
    size_t arg_count = 0;

    for (size_t i = 0; i < (size_t)op->nbr_args + 1; i++) {
        ins_arg_str += u_strspn(ins_arg_str, ", \t");
        arg_buff.sz = u_strccspn(ins_arg_str, ", \t");
        arg_buff.str = ins_arg_str;
        if (arg_buff.str[arg_buff.sz - 1] == '\n')
            arg_buff.str[arg_buff.sz - 1] = '\0';
        if (arg_buff.sz < 1 || *arg_buff.str == '\0')
            continue;
        arg_count++;
        if (!process_arg(rf, &arg_buff, ins, i))
            return -2;
        ins_arg_str = arg_buff.str + arg_buff.sz;
    }
    if (arg_count != (size_t)op->nbr_args)
        return -1;
    return 0;
}

static
bool get_args_result_handling(rf_t *rf, int result)
{
    if (result == -1)
        return (print_error(rf, "Too many arguments given to the instruction.",
            false), false);
    if (result < -1)
        return false;
    return true;
}

bool process_instructions(rf_t *rf)
{
    size_t old_buff_sz;

    for (size_t i = 0; i < rf->ins_table_sz; i++) {
        old_buff_sz = rf->final_buff.sz;
        rf->final_buff.str[rf->final_buff.sz] = rf->ins_table[i].code;
        rf->prog_sz++;
        rf->final_buff.sz++;
        if (rf->ins_table[i].has_cb)
            rf->final_buff.sz++;
        if (!get_args_result_handling(rf, get_args(rf,
            &OP_TAB[rf->ins_table[i].code - 1], &rf->ins_table[i], i)))
            return false;
        if (rf->ins_table[i].has_cb) {
            rf->final_buff.str[old_buff_sz + 1] = rf->ins_table[i].cb << (2 * (
                MAX_ARGS_NUMBER - OP_TAB[rf->ins_table[i].code - 1].nbr_args));
            rf->prog_sz++;
            rf->ins_table[i].size++;
        }
    }
    return true;
}
