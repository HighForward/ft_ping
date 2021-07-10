#include "../includes/ft_ping.h"

int ping_loop(int sockfd, char *target_host, struct sockaddr_in *addr_host, char *ip, t_stats *stats)
{
    ICMP_pckt *tmp;
    ICMP_pckt pckt;
    unsigned char *pck_reply;

    pck_reply = malloc(sizeof(struct ip) + sizeof(ICMP_pckt));
    bzero(stats, sizeof(t_stats));

    gettimeofday(&stats->start, NULL);
    while (!STOP)
    {
        gettimeofday(&stats->start, NULL);

        if (send_data(sockfd, &pckt, stats, addr_host))
            return (str_error("send failed", 1));

        if (recv_data(sockfd , pck_reply, stats, addr_host))
            return str_error("recv failed", 1);

        if (!STOP && stats->pkt_replied)
        {
            gettimeofday(&stats->time_elapsed, NULL);
            update_rtt_average(stats);
            tmp = (ICMP_pckt *) (pck_reply + sizeof(struct ip));
//            printf("%d %d %d %d\n", tmp->hdr.un.echo.id, tmp->hdr.un.echo.sequence, tmp->hdr.code, tmp->hdr.type);
            printf("%lu bytes from %s (%s): icmp_seq=%d ttl=%d time=%.1f ms\n", stats->size_recv - (sizeof(struct ip)) , target_host, ip, tmp->hdr.un.echo.sequence, 64, (float) (((float) stats->time_elapsed.tv_usec - (float) stats->start.tv_usec) / 1000));
            usleep(1000000);
        }
    }
    gettimeofday(&stats->time_elapsed, NULL);
    return (0);
}
