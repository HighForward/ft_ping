#include "../includes/ft_ping.h"


float calculate_average(t_stats *stats, float now)
{
    stats->rtt.hops++;

    if (stats->rtt.hops == 1)
        return (now);
    else if (stats->rtt.hops > 1)
    {
        float total_values = stats->rtt.avg * (float)(stats->rtt.hops - 1);
        total_values += now;

        return total_values / (float)stats->rtt.hops;
    }
}

float calculate_standard_variation(t_stats *stats, float now)
{
    return ((stats->rtt.max - stats->rtt.min) / 2);
}

void update_rtt_average(t_stats *stats)
{
    float now = (float)(stats->time_elapsed.tv_usec - stats->start.tv_usec) / 1000;

    if (stats->rtt.min > now || (int)stats->rtt.min == 0)
        stats->rtt.min = now;
    if (stats->rtt.max < now || (int)stats->rtt.max == 0)
        stats->rtt.max = now;

    stats->rtt.avg = calculate_average(stats, now);
    stats->rtt.mdev = calculate_standard_variation(stats, now);
}