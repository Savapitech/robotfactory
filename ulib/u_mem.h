/*
** EPITECH PROJECT, 2025
** __
** File description:
** _
*/

#ifndef MEM_H
    #define MEM_H
    #include <stddef.h>
    #include <stdint.h>
    #define IDX_OF(array, i, mem_s) (array + ((i) * (mem_s)))

int u_get_array_size(char **);
void *u_memcpy(uint8_t *, uint8_t const *, size_t);
void *u_realloc(void *, size_t, size_t);
void u_swap(int *, int *);
void u_qsort(char *, size_t, size_t,
    int compare(void const *, void const *));

#endif /* MEM_H */
