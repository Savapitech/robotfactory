/*
** EPITECH PROJECT, 2025
** __
** File description:
** _
*/

#ifndef MEM_H
    #define MEM_H
    #include <stdbool.h>
    #include <stddef.h>
    #define IDX_OF(array, i, mem_s) (array + ((i) * (mem_s)))

void *u_memcpy(void *, void const *, size_t);
void *u_realloc(void *, size_t, size_t);
void u_swap(int *, int *);
bool u_bzero(char *restrict str, size_t sz);
int swap_uint32(int src);

#endif /* MEM_H */
