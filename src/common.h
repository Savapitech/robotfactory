/*
** EPITECH PROJECT, 2025
** __
** File description:
** _
*/

#ifndef COMMON_H
    #define COMMON_H
    #include <ctype.h>
    #include <stdbool.h>
    #include <stddef.h>
    #include <stdint.h>

    #include "u_str.h"

    #define WRITE_CONST(fd, str) write(fd, str, sizeof str - 1)
    #define DEFAULT_LINES_CAP 8
    #define SKIP_SPACES(buff) while (isblank(*buff) && *buff != '\0') buff++

enum {
    RETURN_SUCCESS = 0,
    RETURN_FAILURE = 84,
};

typedef struct {
    buff_t name;
    int ins_pos;
} label_t;

typedef struct {
    buff_t buff;
    char code;
    uint8_t cb;
    bool has_cb;
} ins_t;

typedef struct {
    union {
        char reg;
        short idx;
        int dir;
    };
    buff_t *buff;
    size_t size;
} arg_t;

typedef struct {
    // Buffer
    char **lines;
    size_t lines_sz;
    size_t lines_cap;
    size_t lines_i;
    buff_t final_buff;
    size_t lines_total_sz;
    // Compiler
    label_t *lbl_table;
    size_t lbl_table_sz;
    ins_t *ins_table;
    size_t ins_table_sz;
    int prog_sz;
    // Other
    char *file_name;
} rf_t;

void print_error(rf_t *rf, char const *msg, bool warning);
#endif /* COMMON_H */
