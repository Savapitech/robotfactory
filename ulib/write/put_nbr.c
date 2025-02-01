/*
** EPITECH PROJECT, 2024
** SH_PUTNBR
** File description:
** Outputs a given int.
*/

#include "u_write.h"

static void u_put_positive(int nb, int *count)
{
    if (nb > 9)
        u_put_positive(nb / 10, count);
    u_putchar(nb % 10 + '0');
    count++;
}

int u_put_nbr(int nb)
{
    int output = nb;
    int count = 0;

    if (nb < 0) {
        u_putchar('-');
        count++;
        output = -nb;
    }
    if (output < 0) {
        output = -(output / 10);
        u_put_positive(output, &count);
        u_put_positive(-(nb % 10), &count);
    } else
        u_put_positive(output, &count);
    return (0);
}
