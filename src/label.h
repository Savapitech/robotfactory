/*
** EPITECH PROJECT, 2025
** __
** File description:
** _
*/

#ifndef LABEL_H
    #define LABEL_H
    #include <stdbool.h>

    #include "common.h"

typedef struct {
    char *name;
    char *ptr;
} label_t;

bool parse_label_table(rf_t *rf);
#endif /* LABEL_H */
