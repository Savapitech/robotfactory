/*
** EPITECH PROJECT, 2025
** robotfactory
** File description:
** validator2
*/

#include "validator.h"

int check_b_and_skipped(int skipped, char *b[2])
{
    if (b == NULL) {
        if (skipped)
            printf("= ... (%d lines)\n", skipped);
        skipped = 0;
        return 0;
    }
    return 1;
}

int check_s(int skipped, char const *s[2], int size)
{
    if (!memcmp(s[0], s[1], (size_t)size)) {
        skipped++;
        return 0;
    }
    return 1;
}

void check_skipped_value(int skipped)
{
    if (skipped) {
        printf("= ... (%d lines)\n", skipped);
        skipped = 0;
    }
}

size_t showmem(long i, char *b[2], int size)
{
    size_t diff = 0;
    static int skipped = 0;
    char const *s[2];

    if (check_b_and_skipped(skipped, b) == 0)
        return 0;
    s[0] = &b[0][i];
    s[1] = &b[1][i];
    if (check_s(skipped, s, size) == 0)
        return 0;
    check_skipped_value(skipped);
    for (int j = 0; j < 2; j++) {
        printf("%s%c " RESET, !j ? RED : GREEN, "-+"[j]);
        printf("%08x", (int)(s[j] - b[j]));
        diff += show_memblock(s, j, size);
        show_ascii(s, j, size);
        printf("\n");
    }
    return diff;
}

int check_value_f(char **f, long filediff)
{
    if (f[0] == NULL && f[1] == NULL)
        return 0;
    if (f[0] == NULL || f[1] == NULL)
        return (size_t)ABS(filediff);
    return -1;
}

size_t diff(char *left, char *right)
{
    size_t diff = 0;
    long f1_size = file_size(left);
    long f2_size = file_size(right);
    long shortest = MIN(f1_size, f2_size);
    long longest = MAX(f1_size, f2_size);
    long filediff = f1_size - f2_size;
    char *f[2] = { file_read(left), file_read(right) };

    printf("computing diff: [%s] <=> [%s]\n", left, right);
    if (check_value_f(f, filediff) != -1)
        return check_value_f(f, filediff);
    for (int i = 0; shortest > 0; shortest -= 16) {
        diff += showmem(i, f, (int)MIN(shortest, 16L));
        i += 16;
    }
    showmem(0, NULL, 16L);
    if (f1_size != f2_size)
        printf("...missing: %zu bytes\n", longest - shortest);
    return diff + (size_t)ABS(filediff);
}
