/*
** EPITECH PROJECT, 2025
** __
** File description:
** _
*/

#ifndef COMPILER_H
    #define COMPILER_H
    #include <stdbool.h>

    #include "common.h"

bool prepare_compilation(rf_t *rf);
void get_op_code(char *buffer);
#endif /* COMPILER_H */
