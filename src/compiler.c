/*
** EPITECH PROJECT, 2025
** __
** File description:
** _
*/

#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

#include "op.h"
#include "parser.h"
#include "u_mem.h"

static
char *get_header(char *buffer)
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
    name = get_metadata(buffer, NAME_CMD_STRING);
    comment = get_metadata(buffer, COMMENT_CMD_STRING);
    if (name.str == NULL || comment.str == NULL)
        return NULL;
    u_strncpy(header, name.str, name.sz);
    header += header_sz - COMMENT_LENGTH;
    u_strncpy(header, comment.str, comment.sz);
    return header - (header_sz - COMMENT_LENGTH) - sizeof(int);
}

__attribute__((nonnull(1)))
bool prepare_compilation(char *buffer)
{
    char *padded_header = get_header(buffer);

    write(1, padded_header, sizeof(char) * (PROG_NAME_LENGTH +
            COMMENT_LENGTH));
    return true;
}
