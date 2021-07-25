#include "../includes/ft_ping.h"

int isDottedIpAddress(char *ipAddress)
{
    struct sockaddr_in sa;
    int result = inet_pton(AF_INET, ipAddress, &(sa.sin_addr));
    return (result != 0);
}

void print_on_hops(ICMP_pckt *icmp_packet, struct ip ip_packet, t_stats *stats, t_ping_utility *ping_base)
{
//    reverse_dns_lookup(ping_base, ping_base->hit_ip);

    if (icmp_packet->hdr.type == 0 && icmp_packet->hdr.code == 0)
    {
        double after = (double)(((double)(stats->time_elapsed.tv_sec) * 1000) + ((double)(stats->time_elapsed.tv_usec) / 1000));
        double before = (double)(((double)(stats->start.tv_sec) * 1000) + ((double)(stats->start.tv_usec) / 1000));

        if (isDottedIpAddress(ping_base->dns_target) || !ft_strlen(ping_base->fqdn))
        {
            printf("%lu bytes from %s: icmp_seq=%d ttl=%d time=%.1f ms\n", stats->size_recv - (sizeof(struct ip)),
                   ping_base->hit_ip, icmp_packet->hdr.un.echo.sequence, ip_packet.ip_ttl, (after - before));
        }
        else
        {
            printf("%lu bytes from %s (%s): icmp_seq=%d ttl=%d time=%.1f ms\n", stats->size_recv - (sizeof(struct ip)),
                   ping_base->fqdn, ping_base->hit_ip, icmp_packet->hdr.un.echo.sequence, ip_packet.ip_ttl, (after - before));
        }
    }
    else
    {
        if (icmp_packet->hdr.type == 11)
            printf("From %s icmp_seq=%d %s\n", ping_base->hit_ip, stats->pck_send, "Time to live exceeded");
        else
        {
            printf("From %s icmp_seq=%d, Error Type: %d Error Code: %d\n", ping_base->hit_ip, stats->pck_send,
                   icmp_packet->hdr.type, icmp_packet->hdr.code);
        }
    }
}