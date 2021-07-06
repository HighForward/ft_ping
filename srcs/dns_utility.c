#include "../includes/ft_ping.h"

struct sockaddr_in resolve_dns(char *target_host, char **ip)
{
    struct sockaddr_in addr_host;
    bzero(&addr_host, sizeof(struct sockaddr_in));

    struct addrinfo hints;
    memset(&hints, 0, sizeof(struct addrinfo));

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_RAW;
    hints.ai_protocol = IPPROTO_ICMP;
    hints.ai_flags = AI_CANONNAME;

    struct addrinfo *result;

    if (getaddrinfo(target_host, NULL, &hints, &result) != 0)
        printf("getaddrinfo failed: %s\n", strerror(errno));

    struct sockaddr_in *ipv4 = (struct sockaddr_in *)result->ai_addr;
    void *addr = &(ipv4->sin_addr);
    inet_ntop(result->ai_family, addr, (*ip), sizeof(char) * INET_ADDRSTRLEN + 5);

//    while (result)
//    {
//        printf("%s\n", result->ai_addr->sa_data);
//        result = result->ai_next;
//    }

    return ((*ipv4));
}
