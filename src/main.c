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
    rf->lines[rf->lines_sz] = u_strdup(buffer);
    if (rf->lines[rf->lines_sz] == NULL)
        return false;
    U_DEBUG("Line [%lu] [%.*s]\n", rf->lines_sz,
        u_strlen(rf->lines[rf->lines_sz]) - 1, rf->lines[rf->lines_sz]);
    rf->lines_sz++;
    return true;
}

static
bool read_file(char const *path, rf_t *rf)
{
    FILE *file = fopen(path, "r");
    char *buffer = NULL;
    size_t buffer_sz;

    if (file == NULL)
        return NULL;
    rf->lines = (char **)malloc(sizeof *rf->lines * rf->lines_cap);
    if (rf->lines == NULL)
        return (fclose(file), false);
    for (; getline(&buffer, &buffer_sz, file) != -1;) {
        if (u_strlen(buffer) < 2)
            continue;
        if (!fill_line(rf, buffer)) {
            free((void *)rf->lines);
            return (fclose(file), false);
        }
    }
    free(buffer);
    return (fclose(file), true);
}

static
bool handle_file(char const *path)
{
    rf_t rf = { .lines = NULL, .lines_sz = 0, .lines_i = 0,
        .lines_cap = DEFAULT_LINES_CAP, .file_name = path };
    struct stat st;

    if (!read_file(path, &rf))
        return (WRITE_CONST(STDERR_FILENO, "Error: file not exist\n"), false);
    stat(path, &st);
    rf.final_buff.str = malloc(sizeof(char) * (st.st_size + PROG_NAME_LENGTH +
        STRUCT_PADDING + COMMENT_LENGTH));
    if (rf.final_buff.str == NULL)
        return (free((void *)rf.lines), false);
    prepare_compilation(&rf);
    for (size_t i = 0; i < rf.lines_sz; i++)
        free(rf.lines[i]);
    free((void *)rf.lines);
    free(rf.final_buff.str);
    free(rf.lbl_table);
    free(rf.ins_table);
    return true;
}

int main(int ac, char **av)
{
    bool status = true;

    if (ac < 2)
        return 0;
    for (int i = 1; i < ac; i++)
        status &= handle_file(av[i]);
    return status ? RETURN_SUCCESS : RETURN_FAILURE;
}
