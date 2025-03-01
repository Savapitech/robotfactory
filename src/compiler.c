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
bool write_header(rf_t *rf)
{
    size_t header_sz = PROG_NAME_LENGTH + STRUCT_PADDING + COMMENT_LENGTH + 4;
    char *header_str = rf->final_buff.str;
    buff_t name;
    buff_t comment;

    *(uint32_t *)(header_str) = swap_uint32(COREWAR_EXEC_MAGIC);
    header_str += sizeof(int);
    name = get_metadata(rf->lines[rf->lines_i], NAME_CMD_STRING);
    rf->lines_i++;
    comment = get_metadata(rf->lines[rf->lines_i], COMMENT_CMD_STRING);
    rf->lines_i++;
    if (name.str == NULL || comment.str == NULL)
        return false;
    u_strncpy(header_str, name.str, name.sz);
    header_str += header_sz - COMMENT_LENGTH;
    u_strncpy(header_str, comment.str, comment.sz);
    rf->final_buff.sz = header_sz + 8;
    return true;
}

static
bool write_in_file(rf_t *rf)
{
    int new_file_fd;

    u_strcpy(rf->file_name + u_strcspn(rf->file_name, '.') + 1, "cor\0");
    new_file_fd = open(rf->file_name, O_WRONLY | O_CREAT, 0644);
    U_DEBUG("Writing in file [%s]\n", rf->file_name);
    if (new_file_fd == -1)
        return (WRITE_CONST(STDERR_FILENO, "Cannot write in file !\n"), false);
    write(new_file_fd, rf->final_buff.str, rf->final_buff.sz);
    return (close(new_file_fd), true);
}

void print_error(rf_t *rf, char const *msg, bool warning)
{
    if (rf->file_name == NULL)
        return;
    WRITE_CONST(STDERR_FILENO, "asm, ");
    write(STDERR_FILENO, rf->file_name, u_strlen(rf->file_name));
    WRITE_CONST(STDERR_FILENO, ", line ");
    u_putnbr(rf->lines_i + (rf->lines_total_sz - rf->lines_sz));
    WRITE_CONST(STDERR_FILENO, ": " CYAN);
    if (warning)
        WRITE_CONST(STDERR_FILENO, RED "Warning: " CYAN);
    write(STDERR_FILENO, msg, u_strlen(msg));
    WRITE_CONST(STDERR_FILENO, "\n" RESET);
}

__attribute__((nonnull))
bool prepare_compilation(rf_t *rf)
{
    if (!write_header(rf))
        return (WRITE_CONST(STDERR_FILENO, CYAN "Cannot parse header.\n"
            RESET), false);
    if (!parse_label_table(rf))
        return false;
    if (!process_instructions(rf))
        return false;
    return write_in_file(rf);
}
