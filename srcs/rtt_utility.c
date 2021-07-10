#include "../includes/ft_ping.h"

void update_rtt_average(t_stats *stats)
{
    float now = (float)(stats->time_elapsed.tv_usec - stats->start.tv_usec) / 1000;

    if (stats->rtt.min > now || (int)stats->rtt.min == 0)
        stats->rtt.min = now;
    if (stats->rtt.max < now || (int)stats->rtt.max == 0)
        stats->rtt.max = now;

    stats->rtt.avg = (stats->rtt.min + stats->rtt.max) / 2;
}