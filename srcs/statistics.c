#include "../includes/ft_ping.h"

int is_integer(double n)
{
    int X = (int)n;
    double tmp = n - X;

    if (tmp > 0)
        return (0);
    return (1);
}

float get_average_of(float a, float b)
{
    return (100 - (100 * b / a));
}