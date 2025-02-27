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
bool get_args(op_t const *op, ins_t *ins)
{
    char *ins_arg_str = ins->buff.str + ins->buff.sz + 1;
    buff_t arg;
    size_t arg_count = 0;

    for (size_t i = 0; i < (size_t)op->nbr_args + 1; i++) {
        ins_arg_str += u_strspn(ins_arg_str, ", \t");
        arg.sz = u_strccspn(ins_arg_str, ", \t");
        arg.str = ins_arg_str;
        if (arg.str[arg.sz - 1] == '\n')
            arg.str[arg.sz - 1] = '\0';
        if (arg.sz < 1 || *arg.str == '\0')
            continue;
        arg_count++;
        U_DEBUG("Found arg [%.*s] [%.*s]\n", ins->buff.sz, ins->buff.str,
            arg.sz, arg.str);
        ins_arg_str = arg.str + arg.sz;
    }
    if (arg_count != (size_t)op->nbr_args)
        return false;
    return true;
}

bool process_instructions(rf_t *rf)
{
    for (size_t i = 0; i < rf->ins_table_sz; i++) {
        rf->final_buff.str[rf->final_buff.sz] = rf->ins_table[i].code;
        if (!get_args(&OP_TAB[rf->ins_table[i].code - 1],
            &rf->ins_table[i]))
            return (WRITE_CONST(STDERR_FILENO, CYAN "Too many arguments given"
                " to the instruction.\n" RESET));
        rf->final_buff.sz += 1;
    }
    return true;
}
