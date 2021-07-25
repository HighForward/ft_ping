#include "../includes/ft_ping.h"

int perform_t(char *argv, t_options *options)
{
    if (argv)
    {
        int tmp = ft_atoi(argv);
        if (tmp <= 0 || tmp > 255)
        {
            printf("ft_ping: invalid argument: '%s': out of range: 0 <= value <= 255\n", argv);
            exit(1);
        }
        options->t_option = tmp;
        return (0);
    }
    return (1);
}

int perform_w(char *argv, t_options *options)
{
    if (argv)
    {
        for (int i = 0; i < ft_strlen(argv); i++)
        {
            if (ft_isdigit(argv[i]) == 0)
                perform_h();
        }
        int tmp = ft_atoi(argv);

        if (tmp <= 0 || tmp > 65536)
        {
            printf("ft_ping: invalid argument: '%s': out of range: 0 <= value <= 65536\n", argv);
            exit(1);
        }
        options->w_option = (int)tmp;
        return (0);
    }
    return (1);
}

int perform_i(char *argv, t_options *options)
{
    if (argv)
    {
        int tmp = ft_atoi(argv);
        if (tmp <= 0 || tmp > 216000)
        {
            printf("ft_ping: bad timing interval: '%s': 0 <= value <= 216000\n", argv);
            exit(1);
        }
        options->i_option = tmp * 1000000;
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

        if (ft_strlen(arg) == 0)
            perform_h();

        //TODO: -q -W

        if (ft_strncmp(arg, "-h", ft_strlen(arg)) == 0)
            perform_h();
        else if (ft_strncmp(arg, "-v", ft_strlen(arg)) == 0)
            tmp_flag |= V_OPTION;
        else if (ft_strncmp(arg, "-q", ft_strlen(arg)) == 0)
            tmp_flag |= Q_OPTION;
        else if (ft_strncmp(arg, "-t", ft_strlen(arg)) == 0)
        {
            tmp_flag |= T_OPTION;
            if (perform_t(argv[++i], options))
                perform_h();
        }
        else if (ft_strncmp(arg, "-w", ft_strlen(arg)) == 0)
        {
            tmp_flag |= W_OPTION;
            if (perform_w(argv[++i], options))
                perform_h();
        }
        else if (ft_strncmp(arg, "-i", ft_strlen(arg)) == 0)
        {
            tmp_flag |= I_OPTION;
            if (perform_i(argv[++i], options))
                perform_h();
        }
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