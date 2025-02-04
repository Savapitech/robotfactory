/*
** EPITECH PROJECT, 2025
** __
** File description:
** _
*/

#ifndef COMMON_H
    #define COMMON_H

    #define WRITE_CONST(fd, str) write(fd, str, sizeof str)
enum {
    RETURN_SUCCESS = 0,
    RETURN_FAILURE = 84,
};

#endif /* COMMON_H */
