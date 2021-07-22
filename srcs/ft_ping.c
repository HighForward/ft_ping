#include "../includes/ft_ping.h"

void intHandler(int sig)
{
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
    t_stats stats;
    t_ping_utility ping_base;
    bzero(&ping_base, sizeof(ping_base));
    bzero(&ping_base, sizeof(stats));

    signal(SIGINT, intHandler);

    if (parse_args(argv + 1, &ping_base.dns_target,  &ping_base.flag))
        return (1);

    if (toggle_flags(ping_base.flag))
        return (1);

    if (create_socket(&ping_base.sockfd) < 0)
        return (1);

    if (resolve_dns(&ping_base))
        return (1);

    printf("PING %s (%s) %lu(%lu) bytes of data.\n", ping_base.dns_target, ping_base.ip, sizeof(ICMP_pckt), sizeof(ICMP_pckt) + sizeof(struct ip));

    if (ping_loop(&ping_base, &stats))
        return (1);

    print_statistics(&stats, &ping_base);

    close(ping_base.sockfd);

}