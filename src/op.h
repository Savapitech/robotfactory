/*
** EPITECH PROJECT, 2025
** __
** File description:
** _
*/

#ifndef OP_H_
    #define OP_H_
    #include <stddef.h>

    #define MEM_SIZE (6 * 1024)
    #define IDX_MOD 512 /* modulo of the index < */
    #define MAX_ARGS_NUMBER 4 /* this may not be changed 2^*IND_SIZE */

    #define COMMENT_CHAR '#'
    #define LABEL_CHAR ':'
    #define DIRECT_CHAR '%'
    #define SEPARATOR_CHAR ','
    #define INSTRUCTION_CHAR ' '
    #define LABEL_CHARS "abcdefghijklmnopqrstuvwxyz_0123456789"
    #define INSTRUCTION_CHARS "abcdefghijklmnopqrstuvwxyz"

    #define NAME_CMD_STRING ".name"
    #define COMMENT_CMD_STRING ".comment"

    #define REG_NUMBER 16 /* r1 <--> rx */

    #define IS_IDX(opcode) (opcode >= 9 && opcode <= 15 && opcode != 13)
    #define CALC_CB(type) ((type & T_ALL) == T_IND ? 3 : (type & T_ALL))

typedef char args_type_t;

enum {
    T_REG = 1, /* register */
    T_DIR = 2, /* direct (ld #1,r1 put 1 into r1) */
    T_IND = 4, /* indirect always relative */
    T_LAB = 8,

    T_ALL = T_REG | T_IND | T_DIR,
};

typedef struct op_s {
    char const *mnemonique;
    char nbr_args;
    args_type_t type[MAX_ARGS_NUMBER];
    char code;
    int nbr_cycles;
} op_t;

// size (in bytes)
    #define IND_SIZE 2
    #define DIR_SIZE 4
    #define REG_SIZE DIR_SIZE

// op_tab
extern const op_t OP_TAB[];
extern const size_t OP_TAB_SZ;

// header
    #define PROG_NAME_LENGTH 128
    #define COMMENT_LENGTH 2048
    #define COREWAR_EXEC_MAGIC 0xea83f3
    #define STRUCT_PADDING 4

typedef struct header_s {
    int magic;
    char prog_name[PROG_NAME_LENGTH + 1];
    int prog_size;
    char comment[COMMENT_LENGTH + 1];
} header_t;

// live
    #define CYCLE_TO_DIE 1536 /* number of cycle before beig declared dead */
    #define CYCLE_DELTA 5
    #define NBR_LIVE 40
#endif
