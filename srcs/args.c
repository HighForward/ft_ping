#include "../includes/ft_ping.h"

int parse_args(int argc, char **argv, int *flag)
{
    int i = 0;
    char *arg;
    int tmp_flag = 0;

    while (argv[i])
    {
        arg = argv[i++];

        if (strcmp(arg, "-h") == 0)
            tmp_flag |= H_OPTION;
        else if (strcmp(arg, "-v") == 0)
            tmp_flag |= V_OPTION;
    }
    *flag = tmp_flag;
    return (0);
}