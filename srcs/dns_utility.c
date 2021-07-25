#include "../includes/ft_ping.h"

int resolve_dns(t_ping_utility *ping_base)
{
    struct addrinfo hints, *p;
    memset(&hints, 0, sizeof(struct addrinfo));

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_RAW;
    hints.ai_protocol = IPPROTO_ICMP;
    hints.ai_flags = AI_CANONNAME;

    struct addrinfo *result;

    if (getaddrinfo(ping_base->dns_target, NULL, &hints, &result) != 0)
    {
        printf("ft_ping: %s: Name or service not known\n", ping_base->dns_target);
        return (1);
    }
    struct sockaddr_in *ipv4 = (struct sockaddr_in *)result->ai_addr;
    void *addr = &(ipv4->sin_addr);

    ft_bzero(ping_base->ip, INET_ADDRSTRLEN);
    inet_ntop(result->ai_family, addr, ping_base->ip, INET_ADDRSTRLEN);

    (*ping_base).addr_host = (*ipv4);

    freeaddrinfo(result);



    return (0);
}
