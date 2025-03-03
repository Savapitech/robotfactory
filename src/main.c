/*
** EPITECH PROJECT, 2025
** __
** File description:
** _
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#include "common.h"
#include "compiler.h"
#include "debug.h"
#include "op.h"
#include "u_mem.h"
#include "u_str.h"

static
bool ensure_lines_buff_cap(rf_t *rf)
{
    char **new_ptr;

    if (rf->lines_sz < rf->lines_cap - 1)
        return true;
    new_ptr = (char **)u_realloc((char *)rf->lines, sizeof *rf->lines *
        rf->lines_sz, sizeof *rf->lines * rf->lines_cap << 1);
    if (new_ptr == NULL)
        return false;
    rf->lines = new_ptr;
    rf->lines_cap <<= 1;
    return true;
}

static
bool fill_line(rf_t *rf, char *buffer)
{
    ensure_lines_buff_cap(rf);
    SKIP_SPACES(buffer);
    rf->lines[rf->lines_sz] = malloc(sizeof(char) * (u_strlen(buffer) + 2));
    if (rf->lines[rf->lines_sz] == NULL)
        return false;
    u_bzero(rf->lines[rf->lines_sz], u_strlen(buffer) + 2);
    u_strcpy(rf->lines[rf->lines_sz], buffer);
    U_DEBUG("Line [%lu] [%.*s]\n", rf->lines_sz,
        u_strlen(rf->lines[rf->lines_sz]) - 1, rf->lines[rf->lines_sz]);
    rf->lines_sz++;
    return true;
}

static
bool read_lines(FILE *file, rf_t *rf)
{
    char *buffer = NULL;
    size_t buffer_sz;

    for (; getline(&buffer, &buffer_sz, file) != -1;) {
        rf->lines_total_sz++;
        if (u_strlen(buffer) < 2)
            continue;
        if (!fill_line(rf, buffer)) {
            free((void *)rf->lines);
            return (fclose(file), false);
        }
    }
    if (rf->lines_sz < 1)
        return (print_error_no_lines(rf, "The file is empty.", false), false);
    free(buffer);
    return true;
}

static
bool read_file(char const *path, rf_t *rf)
{
    FILE *file = fopen(path, "r");

    if (file == NULL)
        return (WRITE_CONST(STDERR_FILENO, "Error in function open: No such "
            "file or directory.\n"), false);
    rf->lines = (char **)malloc(sizeof *rf->lines * rf->lines_cap);
    if (rf->lines == NULL)
        return (fclose(file), false);
    if (!read_lines(file, rf))
        return false;
    return (fclose(file), true);
}

static
bool handle_file(char const *path, char *file_name)
{
    rf_t rf = { .lines = NULL, .lines_sz = 0, .lines_i = 0,
        .lines_total_sz = 0, .lines_cap = DEFAULT_LINES_CAP,
        .file_name = file_name, .prog_sz = 0 };
    struct stat st;
    size_t header_sz = PROG_NAME_LENGTH + STRUCT_PADDING + COMMENT_LENGTH;

    if (!read_file(path, &rf))
        return false;
    stat(path, &st);
    rf.final_buff.str = malloc(sizeof(char) * (st.st_size + header_sz + 4));
    if (rf.final_buff.str == NULL)
        return (free((void *)rf.lines), false);
    u_bzero(rf.final_buff.str, st.st_size + header_sz + 4);
    prepare_compilation(&rf);
    for (size_t i = 0; i < rf.lines_sz; i++)
        free(rf.lines[i]);
    free((void *)rf.lines);
    free(rf.final_buff.str);
    free(rf.lbl_table);
    return (free(rf.ins_table), true);
}

int main(int ac, char **av)
{
    bool status = true;
    char *file_name;
    int slash_len;
    int file_name_len;

    if (ac < 2)
        return (WRITE_CONST(STDERR_FILENO, "Too few arguments.\n"),
            RETURN_SUCCESS);
    for (int i = 1; i < ac; i++) {
        slash_len = u_strcrspn(av[i], '/') ? u_strcrspn(av[i], '/') + 1 : 0;
        file_name_len = u_strlen(av[i] + slash_len) + 4;
        file_name = malloc(sizeof(char) * file_name_len);
        if (file_name == NULL)
            return RETURN_FAILURE;
        u_strcpy(file_name, av[i] + slash_len);
        status &= handle_file(av[i], file_name);
        free(file_name);
    }
    return status ? RETURN_SUCCESS : RETURN_FAILURE;
}
