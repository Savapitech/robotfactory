/*
** EPITECH PROJECT, 2025
** __
** File description:
** _
*/

#include <fcntl.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

#include "compiler.h"
#include "common.h"
#include "debug.h"
#include "label.h"
#include "op.h"
#include "parser.h"
#include "u_mem.h"

static
int write_header2(size_t header_sz, char *header_str, buff_t *name,
    buff_t *comment)
{
    int result = 0;
    char *after_name = name->str + name->sz + 1;
    char *after_comment = comment->str + comment->sz + 1;

    if (*after_name != '\0' && *after_name != '\n' && *after_name != ' ' &&
        *after_name != '\t') {
        return -5;
    }
    u_strncpy(header_str, name->str, name->sz);
    if (!comment->str)
        result = -2;
    else {
        SKIP_SPACES(after_comment);
        if (isprint(*after_comment))
            return -5;
        header_str += header_sz - COMMENT_LENGTH;
        u_strncpy(header_str, comment->str, comment->sz);
    }
    return result;
}

static
int write_header(rf_t *rf)
{
    size_t header_sz = PROG_NAME_LENGTH + STRUCT_PADDING + COMMENT_LENGTH + 4;
    char *header_str = rf->final_buff.str;
    buff_t name;
    buff_t comment;
    int result = 0;

    *(uint32_t *)(header_str) = swap_uint32(COREWAR_EXEC_MAGIC);
    header_str += sizeof(int);
    name = get_metadata(rf->lines[rf->lines_i], NAME_CMD_STRING);
    if (name.str == NULL)
        return -1;
    rf->lines_i++;
    comment = get_metadata(rf->lines[rf->lines_i], COMMENT_CMD_STRING);
    if (comment.sz > COMMENT_LENGTH || (comment.sz < 1 && comment.str))
        return comment.sz > COMMENT_LENGTH ? -3 : -4;
    if (comment.str)
        rf->lines_i++;
    result = write_header2(header_sz, header_str, &name, &comment);
    rf->final_buff.sz = header_sz + 8;
    return result;
}

static
bool write_in_file(rf_t *rf)
{
    int new_file_fd;
    int prog_sz = __builtin_bswap32(rf->prog_sz);

    u_memcpy(rf->final_buff.str + PROG_NAME_LENGTH + STRUCT_PADDING + 4,
        &prog_sz, sizeof(int));
    u_strcpy(rf->file_name + u_strcspn(rf->file_name, '.') + 1, "cor\0");
    new_file_fd = open(rf->file_name, O_WRONLY | O_CREAT, 0644);
    U_DEBUG("Writing [%d] bytes in file [%s]\n", rf->prog_sz, rf->file_name);
    if (new_file_fd == -1)
        return (WRITE_CONST(STDERR_FILENO, "Cannot write in file !\n"), false);
    write(new_file_fd, rf->final_buff.str, rf->final_buff.sz);
    return (close(new_file_fd), true);
}

void print_error_no_lines(rf_t *rf, char const *msg, bool warning)
{
    if (rf->file_name == NULL)
        return;
    WRITE_CONST(STDERR_FILENO, "asm, ");
    write(STDERR_FILENO, rf->file_name, u_strlen(rf->file_name));
    WRITE_CONST(STDERR_FILENO, ": " CYAN);
    if (warning)
        WRITE_CONST(STDERR_FILENO, RED "Warning: " CYAN);
    write(STDERR_FILENO, msg, u_strlen(msg));
    WRITE_CONST(STDERR_FILENO, "\n" RESET);
}

void print_error(rf_t *rf, char const *msg, bool warning)
{
    if (rf->file_name == NULL)
        return;
    WRITE_CONST(STDERR_FILENO, "asm, ");
    write(STDERR_FILENO, rf->file_name, u_strlen(rf->file_name));
    WRITE_CONST(STDERR_FILENO, ", line ");
    u_putnbr((rf->lines_i + (rf->lines_total_sz - rf->lines_sz)) + 1);
    WRITE_CONST(STDERR_FILENO, ": " CYAN);
    if (warning)
        WRITE_CONST(STDERR_FILENO, RED "Warning: " CYAN);
    write(STDERR_FILENO, msg, u_strlen(msg));
    WRITE_CONST(STDERR_FILENO, "\n" RESET);
}

static
bool write_header_error_handling(rf_t *rf, int write_header_result)
{
    switch (write_header_result) {
        case -1:
            print_error(rf, "No name specified.", false);
            return false;
        case -2:
            print_error(rf, "No comment specified.", true);
            return true;
        case -3:
            print_error(rf, "The comment is too long.", false);
            return false;
        case -4:
            print_error(rf, "No comment specified.", false);
            return false;
    }
    print_error(rf, "Cannot parse header !", false);
    return false;
}

static
void write_lbl_in_fbuff(rf_t *rf)
{
    short bytes_offset = 0;

    for (size_t i = 0; i < rf->ins_table_sz; i++) {
        if (!rf->ins_table[i].lbl_ptr)
            continue;
        bytes_offset = 0;
        for (int j = rf->ins_table[i].ins_i; j <
            rf->ins_table[i].lbl_ins_pos; j++)
            bytes_offset += rf->ins_table[j].size;
        for (size_t j = rf->ins_table[i].lbl_ins_pos; j <
            rf->ins_table[i].ins_i; j++)
            bytes_offset -= rf->ins_table[j].size;
        U_DEBUG("Lbl offset [%d] bytes, ins i [%lu]\n", bytes_offset, i);
        bytes_offset = __builtin_bswap16(bytes_offset);
        u_memcpy(rf->ins_table[i].lbl_ptr, &bytes_offset, sizeof(short));
    }
}

__attribute__((nonnull))
bool prepare_compilation(rf_t *rf)
{
    int write_header_result;

    if (rf->name_count > 1)
        return (print_error_no_lines(rf, "Double name def", false), false);
    if (rf->comment_count > 1)
        return (print_error_no_lines(rf, "Double comment def", false), false);
    write_header_result = write_header(rf);
    if (write_header_result < 0)
        if (!write_header_error_handling(rf, write_header_result))
            return false;
    if (!parse_label_table(rf))
        return false;
    if (!process_instructions(rf))
        return false;
    write_lbl_in_fbuff(rf);
    return write_in_file(rf);
}
