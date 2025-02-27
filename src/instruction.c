/*
** EPITECH PROJECT, 2025
** __
** File description:
** _
*/

#include <stdbool.h>
#include <stdint.h>
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
bool write_value(rf_t *rf, arg_t *arg)
{
    char *fbuff_ptr = rf->final_buff.str + rf->final_buff.sz;

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
    U_DEBUG(RED "Writing [%lu] byte%s value [%d]\n" RESET, arg->size,
        (arg->size > 1 ? "s" : ""), arg->dir);
    return true;
}

static
bool process_arg(rf_t *rf, buff_t *arg_buffp, ins_t *ins)
{
    arg_t arg = { .buff = arg_buffp, .size = sizeof(char) };
    char type = get_arg_type(arg.buff->str);

    U_DEBUG("Type [%d]\n", type);
    if (type & T_REG) {
        arg.buff->str++;
        if (!u_strnum(arg.buff->str, &arg.dir) || !arg.dir || arg.dir >
            REG_NUMBER)
            return (WRITE_CONST(STDERR_FILENO, "Invalid reg nbr.\n"), false);
        write_value(rf, &arg);
    }
    arg.size = (!(type & T_DIR) || IS_IDX(ins->code))
        ? sizeof(short) : sizeof(int);
    if (type & T_DIR && !(type & T_LAB)) {
        arg.buff->str++;
        if (!u_strnum(arg.buff->str, &arg.dir))
            return false;
        write_value(rf, &arg);
    }
    return true;
}

static
bool get_args(rf_t *rf, op_t const *op, ins_t *ins, size_t ins_idx)
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
        U_DEBUG("Found arg [%.*s] [%.*s]\n", ins->buff.sz, ins->buff.str,
            arg_buff.sz, arg_buff.str);
        process_arg(rf, &arg_buff, ins);
        ins_arg_str = arg_buff.str + arg_buff.sz;
    }
    if (arg_count != (size_t)op->nbr_args)
        return false;
    return true;
}

bool process_instructions(rf_t *rf)
{
    for (size_t i = 0; i < rf->ins_table_sz; i++) {
        rf->final_buff.str[rf->final_buff.sz] = rf->ins_table[i].code;
        rf->final_buff.sz++;
        if (!get_args(rf, &OP_TAB[rf->ins_table[i].code - 1],
            &rf->ins_table[i], i))
            return (WRITE_CONST(STDERR_FILENO, CYAN "Too many arguments given"
                " to the instruction.\n" RESET));
    }
    return true;
}
