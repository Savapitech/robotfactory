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
bool process_instructions(rf_t *rf);
#endif /* COMPILER_H */
