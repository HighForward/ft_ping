#include "../includes/ft_ping.h"

int toggle_flags(int flag)
{
    if ((flag & (1 << H_BIT)) > 0)
        printf("H ok\n");
    if ((flag & (1 << V_BIT)) > 0)
        printf("V ok\n");
    return (0);
}