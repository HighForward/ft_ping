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

void print_statistics(t_stats *stats, t_ping_utility *ping_base)
{
    printf("--- %s ping statistics ---\n", ping_base->dns_target);

    float average_loss = get_average_of((float)stats->pck_send, (float)stats->pck_recv);
    int type = is_integer(average_loss);

    double secs = (double)(stats->latest_pckt.tv_usec - stats->begin_pgrm.tv_usec) / 1000000 + (double)(stats->latest_pckt.tv_sec - stats->begin_pgrm.tv_sec);

    printf("%d packets transmitted, %d received, %.*f%% packets lost, time %.2fs\n", stats->pck_send, stats->pck_recv, (type == 0 ? 4 : 0), average_loss, secs);
    if (stats->rtt.hops > 0)
        printf("rtt min/avg/max/mdev = %.3f/%.3f/%.3f/%.3f ms\n", stats->rtt.min, stats->rtt.avg, stats->rtt.max, stats->rtt.mdev);

}