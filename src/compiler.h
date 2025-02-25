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

typedef struct {
    char *name;
    char *ptr;
} label_t;

bool prepare_compilation(rf_t *rf);
#endif /* COMPILER_H */
