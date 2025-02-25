/*
** EPITECH PROJECT, 2025
** robotfactory
** File description:
** get_op_code
*/

#include <fcntl.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

#include "common.h"
#include "debug.h"
#include "op.h"
#include "parser.h"
#include "u_mem.h"

buff_t get_instruction(char *line)
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

bool check_instruction(buff_t buff)
{
    for (size_t i = 0; i < OP_TAB_SZ; i++) {
        if (u_strncmp(OP_TAB[i].mnemonique, buff.str, buff.sz) == 0) {
            return true;
        }
    }
    return false;
}


// FAIRE FONCTION QUI PREND UNE LIGNE, SI INSTRUCTION DEDANS : RENVOIE L'INS. // SINON RENVOIE RIEN ):<
void get_op_code(rf_t *rf)
{
    buff_t buff = {NULL, 0};

    for (size_t i = rf->lines_i; i < rf->lines_sz; i++) {
        buff = get_instruction(rf->lines[i]);
        if (buff.str == NULL)
            continue;
        if (!check_instruction(buff)) {
            WRITE_CONST(STDERR_FILENO, CYAN "Invalid instruction.\n" RESET);
            return;
        }
    }
}