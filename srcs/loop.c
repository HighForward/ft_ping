#include "../includes/ft_ping.h"

int ping_loop(int sockfd, char *target_host, struct sockaddr_in *addr_host, char *ip, t_stats *stats)
{
    ICMP_pckt *tmp;
    ICMP_pckt pckt;
    struct sockaddr_in hit_addr;
    unsigned char *pck_reply;
    pck_reply = malloc(sizeof(struct ip) + sizeof(ICMP_pckt));
    bzero(stats, sizeof(t_stats));

    gettimeofday(&stats->start, NULL);
    while (!STOP)
    {
        bzero(&hit_addr, sizeof(hit_addr));
        gettimeofday(&stats->start, NULL);

        if (send_data(sockfd, &pckt, stats, addr_host))
            return (str_error("send failed", 1));

        if (recv_data(sockfd , pck_reply, stats, addr_host, &hit_addr))
            return str_error("recv failed", 1);

        if (!STOP && stats->pkt_replied)
        {
            gettimeofday(&stats->time_elapsed, NULL);
            update_rtt_average(stats);
            tmp = (ICMP_pckt *) (pck_reply + sizeof(struct ip));
            print_on_hops(tmp, stats, target_host, pck_reply, hit_addr);
            usleep(1000000);
        }
    }
    gettimeofday(&stats->time_elapsed, NULL);
    return (0);
}
