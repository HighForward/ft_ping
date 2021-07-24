#include "../includes/ft_ping.h"

void print_on_hops(ICMP_pckt *icmp_packet, struct ip ip_packet, t_stats *stats, t_ping_utility *ping_base)
{
    char hit_ip[INET_ADDRSTRLEN];

    inet_ntop(ping_base->addr_hit.sin_family, &ping_base->addr_hit.sin_addr, hit_ip, INET_ADDRSTRLEN);

    if (icmp_packet->hdr.type == 0 && icmp_packet->hdr.code == 0)
    {
        stats->success_hop = 1;
        double after = (double)(((double)(stats->time_elapsed.tv_sec) * 1000) + ((double)(stats->time_elapsed.tv_usec) / 1000));
        double before = (double)(((double)(stats->start.tv_sec) * 1000) + ((double)(stats->start.tv_usec) / 1000));
        printf("%lu bytes from %s (%s): icmp_seq=%d ttl=%d time=%.1f ms\n", stats->size_recv - (sizeof(struct ip)),
               ping_base->dns_target, hit_ip, icmp_packet->hdr.un.echo.sequence, ip_packet.ip_ttl, (after - before));

    }
    else
    {
        if (icmp_packet->hdr.type == 11)
            printf("From %s icmp_seq=%d %s\n", hit_ip, stats->pck_send, "Time to live exceeded");
        else
        {
            printf("From %s icmp_seq=%d %s\n", hit_ip, stats->pck_send, "Unhandled error");
        }
    }
}