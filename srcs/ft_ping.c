#include "../includes/ft_ping.h"

int STOP = 0;

void intHandler(int sig) {
    STOP = 1;
    write(1, "\n", 1);
}

int str_error(char *str, int code)
{
    printf("%s\n", str);
    return (code);
}

int create_socket(int *sockfd)
{
    int ttl = 64;
    struct timeval tv_out;

    tv_out.tv_sec = 1;
    tv_out.tv_usec = 0;

    (*sockfd) = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);

    if ((*sockfd) < 0)
        return str_error("Socket file descriptor not received!", -1);

    if (setsockopt((*sockfd), SOL_IP, IP_TTL, &ttl, sizeof(ttl)) != 0)
        return str_error("Setting socket options to TTL failed!", -1);
    if (setsockopt((*sockfd), SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv_out, sizeof(tv_out)) != 0)
        return str_error("Setting socket timeout option failed!", -1);

    return (1);
}

int main(int argc, char **argv)
{
    char *dns_target = argv[1];
    struct sockaddr_in addr_host;
    char *ip;
    int sockfd;

    signal(SIGINT, intHandler);

    if (create_socket(&sockfd) < 0)
        return (-1);

    addr_host = resolve_dns(dns_target, &ip);

    t_stats stats;
    ICMP_pckt *tmp;
    ICMP_pckt pckt;

    bzero(&stats, sizeof(t_stats));
    stats.r_addr_len = sizeof(stats.r_addr);

    printf("PING %s (%s) %lu(%lu) bytes of data\n", dns_target, ip, sizeof(ICMP_pckt), sizeof(ICMP_pckt) + sizeof(struct ip));
    unsigned char *pck_reply = (unsigned char *) malloc(sizeof(struct ip) + sizeof(ICMP_pckt));

    gettimeofday(&stats.start, NULL);
    while (!STOP)
    {
        stats.pkt_replied = 0;
        gettimeofday(&stats.start, NULL);
        fill_icmp_packet(&pckt);

        if (sendto(sockfd, &pckt, sizeof(pckt), 0, (struct sockaddr *) &addr_host, sizeof(struct sockaddr)) < 0)
            return str_error(strerror(errno), 1);

        stats.pck_send++;

        if (recvfrom(sockfd, pck_reply, sizeof(struct ip) + sizeof(ICMP_pckt), 0, (struct sockaddr *) &stats.r_addr, &stats.r_addr_len) >= 0)
        {
            stats.pck_recv++;
            stats.pkt_replied = 1;
        }

        if (!STOP && stats.pkt_replied)
        {
            gettimeofday(&stats.time_elapsed, NULL);
            tmp = (ICMP_pckt *) (pck_reply + sizeof(struct ip));

            printf("%lu bytes from %s (%s): icmp_seq=%d ttl=%d time=%.1f ms\n", sizeof(ICMP_pckt) , dns_target, ip, tmp->hdr.un.echo.sequence, 64, (float) (((float) stats.time_elapsed.tv_usec - (float) stats.start.tv_usec) / 1000));
            usleep(1000000);
        }
    }

    gettimeofday(&stats.time_elapsed, NULL);
    printf("--- %s ping statistics ---\n", dns_target);

    float average_loss = get_average_of(stats.pck_send, stats.pck_recv);
    int type = is_integer(average_loss);
    printf("%d packets transmitted, %d received, %.*f%% packets lost, time %ld\n", stats.pck_send, stats.pck_recv, (type == 0 ? 4 : 0), average_loss, (stats.time_elapsed.tv_usec - stats.start.tv_usec) / 1000);
}