#include "../includes/ft_ping.h"

void perform_h()
{
    printf("\nUsage\n\tft_ping [options] <destination>\n\n");
    printf("Options:\n");
    printf("\t<destination>      dns name or ip address\n");
    printf("\t-h                 print help and exit\n");
    printf("\t-v                 verbose output\n");
    printf("\t-t <ttl>           define time to live\n");
    printf("\t-i <interval>      seconds between sending each packet\n");
    printf("\t-w <deadline>      reply wait <deadline> in seconds\n");
    printf("\t-q                 quiet output\n");

    exit(1);
}

int exec_w(t_ping_utility *ping_base)
{
    if (((ping_base->flag & (1 << W_BIT)) > 0))
    {
        ping_base->options.w_option--;
        if (ping_base->options.w_option == 0)
            return (1);
    }
    return (0);
}

int toggle_flags(int flag, t_options *options)
{
//    if ((flag & (1 << H_BIT)) > 0)
//        perform_h();
//    if ((flag & (1 << V_BIT)) > 0)
//        printf("V ok\n");
    if ((flag & (1 << T_BIT)) <= 0 && options->t_option == 0)
        options->t_option = 128;
    if ((flag & (1 << I_BIT)) <= 0 && options->i_option == 0)
        options->i_option = 1 * 1000000;
    return (0);
}