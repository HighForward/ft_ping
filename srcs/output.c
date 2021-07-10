#include "../includes/ft_ping.h"

void print_on_hops(ICMP_pckt *pckt, t_stats *stats, char *target_host, unsigned char *reply, struct sockaddr_in hit_addr)
{
    char hit_ip[INET_ADDRSTRLEN];

    struct ip structip;
    memcpy(&structip, reply, 20);

    inet_ntop(hit_addr.sin_family, &hit_addr.sin_addr, hit_ip, INET_ADDRSTRLEN);

    if (pckt->hdr.type == 0 && pckt->hdr.code == 0)
        printf("%lu bytes from %s (%s): icmp_seq=%d ttl=%d time=%.1f ms\n", stats->size_recv - (sizeof(struct ip)) , target_host, hit_ip, pckt->hdr.un.echo.sequence, structip.ip_ttl, (float)(((float)stats->time_elapsed.tv_usec - (float)stats->start.tv_usec) / 1000));
    else
    {
        if (pckt->hdr.type == 11)
            printf("From %s icmp_seq=%d %s\n", hit_ip, stats->pck_send, "Time to live exceeded");
    }
}