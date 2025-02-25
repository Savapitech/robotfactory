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

#include "common.h"
#include "debug.h"
#include "op.h"
#include "parser.h"
#include "u_mem.h"

static
char *get_header(rf_t *rf)
{
    size_t header_sz = PROG_NAME_LENGTH + STRUCT_PADDING + COMMENT_LENGTH;
    char *header = malloc(sizeof(char) * header_sz);
    buff_t name;
    buff_t comment;

    if (header == NULL)
        return NULL;
    u_bzero(header, header_sz);
    *(uint32_t *)(header) = swap_uint32(COREWAR_EXEC_MAGIC);
    header += sizeof(int);
    name = get_metadata(rf->lines[rf->lines_i], NAME_CMD_STRING);
    rf->lines_i++;
    comment = get_metadata(rf->lines[rf->lines_i], COMMENT_CMD_STRING);
    rf->lines_i++;
    if (name.str == NULL || comment.str == NULL)
        return NULL;
    u_strncpy(header, name.str, name.sz);
    header += header_sz - COMMENT_LENGTH;
    u_strncpy(header, comment.str, comment.sz);
    return header - (header_sz - COMMENT_LENGTH) - sizeof(int);
}

__attribute__((nonnull(1)))
bool prepare_compilation(rf_t *rf)
{
    char *padded_header = get_header(rf);
    char new_file_name[u_strlen(rf->file_name) + 2];
    char const *file_name = rf->file_name;
    int new_file_fd;

    file_name += u_strcspn(rf->file_name, '/') + 1;
    u_strcpy(new_file_name, file_name);
    new_file_name[u_strcspn(new_file_name, '.') + 1] = 'c';
    new_file_name[u_strcspn(new_file_name, '.') + 2] = 'o';
    new_file_name[u_strcspn(new_file_name, '.') + 3] = 'r';
    new_file_name[u_strcspn(new_file_name, '.') + 4] = '\0';
    new_file_fd = open(new_file_name, O_WRONLY | O_CREAT, 0644);
    U_DEBUG("Writing in file [%s]\n", new_file_name);
    if (new_file_fd == -1)
        return (WRITE_CONST(STDERR_FILENO, "Cannot write in file !\n"), false);
    write(new_file_fd, padded_header, sizeof(char) * (PROG_NAME_LENGTH +
            COMMENT_LENGTH));
    close(new_file_fd);
    return true;
}
