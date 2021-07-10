#include "../includes/ft_ping.h"

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
    int ttl = 128;
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
    t_stats stats;
    char *ip;
    int sockfd;

    signal(SIGINT, intHandler);

    if (create_socket(&sockfd) < 0)
        return (1);

    if (resolve_dns(dns_target, &addr_host, &ip))
        return (1);

    printf("PING %s (%s) %lu(%lu) bytes of data.\n", dns_target, ip, sizeof(ICMP_pckt), sizeof(ICMP_pckt) + sizeof(struct ip));

    if (ping_loop(sockfd, dns_target, &addr_host, ip, &stats))
        return (1);

    printf("--- %s ping statistics ---\n", dns_target);

    float average_loss = get_average_of(stats.pck_send, stats.pck_recv);
    int type = is_integer(average_loss);

    printf("%d packets transmitted, %d received, %.*f%% packets lost, time %ldms\n", stats.pck_send, stats.pck_recv, (type == 0 ? 4 : 0), average_loss, (stats.time_elapsed.tv_usec - stats.start.tv_usec) / 1000);
    if (stats.rtt.hops > 0)
        printf("rtt min/avg/max/mdev = %.3f/%.3f/%.3f/%.3f ms\n", stats.rtt.min, stats.rtt.avg, stats.rtt.max, stats.rtt.mdev);
}