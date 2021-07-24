#include "../includes/ft_ping.h"

int ping_loop(t_ping_utility *ping_base, t_stats *stats)
{
    struct ICMP_pckt *tmp_icmp;
    struct ip tmp_ip;
    unsigned char pck_reply[(sizeof(struct ip) + 4 + sizeof(struct ip) + sizeof(struct ICMP_pckt))];
    ft_bzero(&(*stats), sizeof(t_stats));
    ft_bzero(&ping_base->send_pckt, sizeof(struct ICMP_pckt));

    gettimeofday(&stats->start, NULL);
    gettimeofday(&stats->begin_pgrm, NULL);
    while (!STOP)
    {
        ft_bzero(pck_reply, sizeof(pck_reply));
        ft_bzero(&ping_base->addr_hit, sizeof(ping_base->addr_hit));
        gettimeofday(&stats->start, NULL);

        if (send_data(stats, ping_base))
            return (str_error("send failed", 1));

        if (recv_data(pck_reply, stats, ping_base))
            return str_error("recv failed", 1);

        if (!STOP && stats->pkt_replied)
        {
            gettimeofday(&stats->time_elapsed, NULL);
            update_rtt_average(stats);

            tmp_icmp = (ICMP_pckt *) (pck_reply + sizeof(struct ip));
            memcpy(&tmp_ip, pck_reply, 20);

            print_on_hops(tmp_icmp, tmp_ip, stats, ping_base);

            gettimeofday(&stats->latest_pckt, NULL);
            usleep(ping_base->options.i_option);
        }
        else if (!STOP && stats->size_recv < 0)
        {
            if ((ping_base->flag & (1 << V_BIT)) > 0)
                printf("time out: no response found!\n");
        }

        if (exec_w(ping_base))
            break ;

    }
    gettimeofday(&stats->time_elapsed, NULL);
    gettimeofday(&stats->latest_pckt, NULL);
    return (0);
}
