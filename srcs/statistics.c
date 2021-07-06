#include "../includes/ft_ping.h"

int is_integer(double N)
{
    int X = N;
    double temp2 = N - X;

    if (temp2 > 0)
        return (0);
    return (1);
}

float get_average_of(float a, float b)
{

    float result = a / b;
    float reverse = 100 / result;
    float tmp = 100;
    return (tmp - reverse);
}