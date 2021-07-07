#include "../includes/ft_ping.h"

int resolve_dns(char *target_host, struct sockaddr_in *addr_host,char **ip)
{
    struct addrinfo hints;
    memset(&hints, 0, sizeof(struct addrinfo));

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_RAW;
    hints.ai_protocol = IPPROTO_ICMP;
    hints.ai_flags = AI_CANONNAME;

    struct addrinfo *result;

    if (getaddrinfo(target_host, NULL, &hints, &result) != 0)
    {
        printf("getaddrinfo: %s\n", strerror(errno));
        return (1);
    }
    struct sockaddr_in *ipv4 = (struct sockaddr_in *)result->ai_addr;
    void *addr = &(ipv4->sin_addr);

    (*ip) = malloc(sizeof(char) * INET_ADDRSTRLEN + 4);
    bzero((*ip), INET_ADDRSTRLEN + 4);
    inet_ntop(result->ai_family, addr, (*ip), sizeof(char) * INET_ADDRSTRLEN + 5);

    (*addr_host) = (*ipv4);
    return (0);
}
