/*
** EPITECH PROJECT, 2025
** __
** File description:
** _
*/

#include <unistd.h>

#include "u_str.h"


static
void u_putchar(char c)
{
    write(STDOUT_FILENO, &c, 1);
}

static
int cycle_negative(int n)
{
    int reduced = -(n / 10);

    write(STDOUT_FILENO, "-", 1);
    if (reduced)
        u_putnbr(reduced);
    return -(n % 10);
}

int u_putnbr(int n)
{
    if (n < 0)
        n = cycle_negative(n);
    if (n > 9)
        u_putnbr(n / 10);
    u_putchar((n % 10) | '0');
    return 0;
}
