#include "../includes/ft_ping.h"

void perform_h()
{
    printf("\nUsage\n\tft_ping [options] <destination>\n\n");
    printf("Options:\n");
    printf("\t<destination>      dns name or ip address\n");
    printf("\t-h                 print help and exit\n");
    printf("\t-v                 verbose output\n");
    printf("\t-t <ttl>           define time to live\n");
    printf("\t-i <interval>      seconds between sending each packet (TODO)\n");
    exit(1);
}

int toggle_flags(int flag, t_options *options)
{
//    if ((flag & (1 << H_BIT)) > 0)
//        perform_h();
//    if ((flag & (1 << V_BIT)) > 0)
//        printf("V ok\n");
    if ((flag & (1 << T_BIT)) <= 0 && options->t_option == 0)
        options->t_option = 128;
    return (0);
}