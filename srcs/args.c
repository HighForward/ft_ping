#include "../includes/ft_ping.h"

int perform_t(char *argv, t_options *options)
{
    if (argv)
    {
        int tmp = atoi(argv);
        if (tmp <= 0 || tmp > 255)
        {
            printf("ft_ping: invalid argument: '%d': out of range: 0 <= value <= 255\n", tmp);
            exit(1);
        }
        options->t_option = tmp;
        return (0);
    }
    return (1);
}

int parse_args(char **argv, char **dns_target, int *flag, t_options *options)
{
    int i = 0;
    char *arg;
    int tmp_flag = 0;
    while (argv[i])
    {
        arg = argv[i];

        if (strcmp(arg, "-h") == 0)
            perform_h();
        else if (strcmp(arg, "-v") == 0)
            tmp_flag |= V_OPTION;
        else if (strcmp(arg, "-t") == 0)
        {
            tmp_flag |= T_OPTION;
            if (perform_t(argv[++i], options))
                perform_h();
        }
        else if (strcmp(arg, "-w") == 0)
        {}
        else if (strcmp(arg, "-i") == 0)
        {}
        else if (!(*dns_target))
            *dns_target = argv[i];
        else
            perform_h();
        i++;
    }

    if (!(*dns_target))
        perform_h();

    *flag = tmp_flag;
    return (0);
}