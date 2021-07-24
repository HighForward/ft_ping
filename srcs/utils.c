#include "../includes/ft_ping.h"

int	ft_atoi(const char *nptr)
{
    unsigned int		i;
    unsigned long int	nb;
    unsigned long int	less;

    less = 1;
    i = 0;
    nb = 0;
    while ((nptr[i] == '\t' || nptr[i] == '\n' || nptr[i] == '\v' ||
            nptr[i] == '\f' || nptr[i] == '\r' || nptr[i] == ' '))
        i++;
    if (nptr[i] == '-' || nptr[i] == '+')
    {
        if (nptr[i] == '-')
            less = -1;
        i++;
    }
    while (nptr[i] && nptr[i] >= '0' && nptr[i] <= '9')
        nb = nb * 10 + (unsigned long int)(nptr[i++] - 48);
    if (nb > 9223372036854775807 && less == (unsigned long int)-1)
        return (0);
    else if (nb > 9223372036854775807)
        return (-1);
    return (nb * less);
}

void	ft_bzero(void *s, size_t n)
{
    unsigned char	*d;
    unsigned int	i;

    d = (unsigned char*)s;
    i = 0;
    while (i < n)
    {
        d[i] = 0;
        i++;
    }
    s = (void*)d;
}

int	ft_isdigit(int c)
{
    if (c >= '0' && c <= '9')
        return (1);
    return (0);
}

char	*ft_strcpy(char *dest, char *src)
{
    int i;

    i = 0;
    while (src[i])
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return (dest);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
    unsigned int	i;
    unsigned char	*s;
    unsigned char	*d;

    s = (unsigned char*)s1;
    d = (unsigned char*)s2;
    i = 0;
    while (i < n - 1 && s[i] && d[i] && s[i] == d[i])
        i++;
    if (n > 0)
        return (s[i] - d[i]);
    else
        return (0);
}

int	ft_strlen(const char *str)
{
    int i;

    i = 0;
    if (!str)
        return (0);
    while (str[i])
        i++;
    return (i);
}