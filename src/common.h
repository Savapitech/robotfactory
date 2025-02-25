/*
** EPITECH PROJECT, 2025
** __
** File description:
** _
*/

#ifndef COMMON_H
    #define COMMON_H
    #include <stddef.h>
    #define WRITE_CONST(fd, str) write(fd, str, sizeof str - 1)
    #define DEFAULT_LINES_CAP 8

enum {
    RETURN_SUCCESS = 0,
    RETURN_FAILURE = 84,
};

typedef struct {
    char **lines;
    size_t lines_sz;
    size_t lines_cap;
    size_t lines_i;
    char const *file_name;
} rf_t;

#endif /* COMMON_H */
