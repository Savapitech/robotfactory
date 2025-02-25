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


// FAIRE FONCTION QUI PREND UNE LIGNE, SI INSTRUCTION DEDANS : RENVOIE L'INS. // SINON RENVOIE RIEN ):<
void get_op_code(rf_t *rf)
{
    buff_t buff = {NULL, 0};
    printf("OP TAB : \n%s\n", OP_TAB[0].mnemonique);
    U_DEBUG("len OP_TAB[0][0] : %d\n", u_strlen(OP_TAB[0].mnemonique));

    for (size_t i = rf->lines_i; i < rf->lines_sz; i++) {
        buff = get_instruction(rf->lines[i]);
        if (buff.str == NULL)
            continue;
        U_DEBUG("found intrustion : %.*s\n", buff.sz, buff.str);
    }


    // for (size_t i = rf->lines_i; i < rf->lines_sz; i++) {
    //     U_DEBUG("lines [%lu] : %s\n", i, rf->lines[i]);
    //     for (size_t j = 0; i < OP_TAB_SZ; j++) {
    //         if (u_strncmp(rf->lines[i], OP_TAB[j].mnemonique, u_strlen(OP_TAB[j].mnemonique)) == 0) {
    //             U_DEBUG("voilà : %s\n", OP_TAB[j].mnemonique);
    //         }
    //     }
    // }


}