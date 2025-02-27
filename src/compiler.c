/*
** EPITECH PROJECT, 2025
** __
** File description:
** _
*/

#include <fcntl.h>
#include <stdbool.h>
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
    size_t header_sz = PROG_NAME_LENGTH + STRUCT_PADDING + COMMENT_LENGTH;
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
    rf->final_buff.sz = header_sz;
    return true;
}

static
bool write_in_file(rf_t *rf)
{
    char new_file_name[u_strlen(rf->file_name) + 2];
    char const *file_name = rf->file_name;
    int new_file_fd;

    file_name += u_strcspn(rf->file_name, '/') + 1;
    u_strcpy(new_file_name, file_name);
    u_strcpy(new_file_name + u_strcspn(new_file_name, '.') + 1, "cor\0");
    new_file_fd = open(new_file_name, O_WRONLY | O_CREAT, 0644);
    U_DEBUG("Writing in file [%s]\n", new_file_name);
    if (new_file_fd == -1)
        return (WRITE_CONST(STDERR_FILENO, "Cannot write in file !\n"), false);
    write(new_file_fd, rf->final_buff.str, rf->final_buff.sz);
    return (close(new_file_fd), true);
}

__attribute__((nonnull(1)))
bool prepare_compilation(rf_t *rf)
{
    if (!write_header(rf))
        return (WRITE_CONST(STDERR_FILENO, CYAN "Cannot parse header.\n"
            RESET), false);
    parse_label_table(rf);
    process_instructions(rf);
    return write_in_file(rf);
}
