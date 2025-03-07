/*
** EPITECH PROJECT, 2025
** robotfactory
** File description:
** validator
*/

#ifndef VALIDATOR_H_
    #define VALIDATOR_H_

    #include <ctype.h>
    #include <fcntl.h>
    #include <stdarg.h>
    #include <stdbool.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <sys/stat.h>
    #include <unistd.h>
    #include <stddef.h>

    #define ABS(x) (((x) > 0) ? (x) : (-x))
    #define MIN(x, y) (((x) < (y)) ? (x) : (y))
    #define MAX(x, y) (((x) > (y)) ? (x) : (y))
    #define CFMT(n) "\033[" #n "m"

    #define RESET CFMT(0)
    #define BOLD CFMT(1)

    #define RED CFMT(31)
    #define GREEN CFMT(32)
    #define YELLOW CFMT(33)
    #define BLUE CFMT(34)
    #define PURPLE CFMT(35)
    #define CYAN CFMT(36)

    #define GET_STATUS(st) ((st) ? EXIT_KO : EXIT_OK)

    #define CLENGTH_OF(arr) (sizeof (arr) / sizeof *(arr))
    #define SSTR_UNPACK(s) s, SSTRLEN(s)
    #define SSTRLEN(s) ((sizeof(s) - 1) / sizeof(char))

int check_b_and_skipped(int skipped, char *b[2]);
int check_s(int skipped, char const *s[2], int size);
void check_skipped_value(int skipped);
size_t showmem(long i, char *b[2], int size);
off_t ql_file_size(char const *filepath);
int check_value_f(char **f, long filediff);
char *ql_file_read(char const *filepath);
int ql_file_read_n(char const *filepath, char *buff, size_t size);
size_t show_memblock(char const *s[2], int j, int n);
void pad_emptyness(int group, int n);
void show_ascii(char const *s[2], int j, int n);
size_t diff(char *left, char *right);



#endif /* !VALIDATOR_H_ */
