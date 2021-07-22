#include "../includes/ft_ping.h"

int parse_args(char **argv, char **dns_target, int *flag)
{
    int i = 0;
    char *arg;
    int tmp_flag = 0;
    while (argv[i])
    {
        arg = argv[i];

        if (strcmp(arg, "-h") == 0)
        {
            perform_h();
            tmp_flag |= H_OPTION;
            exit(1);
        }
//        else if (strcmp(arg, "-v") == 0)
//            tmp_flag |= V_OPTION;
        else if (!(*dns_target))
            *dns_target = argv[i];
        else
            perform_h();
        i++;
    }


    *flag = tmp_flag;
    return (0);
}