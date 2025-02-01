/*
** EPITECH PROJECT, 2025
** __
** File description:
** _
*/

#ifndef WRITE_H
    #define WRITE_H

int u_printf(char *, ...);
int u_putchar(char);
int u_put_nbr(int);
int u_put_unsigned_nbr(unsigned int);
int u_put_hexa(int);
int u_put_address(int);
int u_put_hexa_upper(int);
int u_put_octal(int);
int u_put_float(float);
int u_put_float_upper(float);
void u_put_float2(int *, int, int, int);
void u_put_float2_upper(int *, int, int, int);
int u_putstr(char const *);
int u_puterr(char const *);
int u_showstr(char const *);
int u_showmem(char const *, int);
int u_show_word_array(char *const *);

#endif /* WRITE_H */
