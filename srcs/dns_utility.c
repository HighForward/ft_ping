#include "../includes/ft_ping.h"

void fqdn_lookup(char *target_host)
{
    struct addrinfo hints;
    memset(&hints, 0, sizeof(struct addrinfo));

    hints.ai_family = AF_INET;    /* Allow IPv4 or IPv6 */
    hints.ai_socktype = SOCK_RAW; /* Datagram socket */
    hints.ai_protocol = IPPROTO_ICMP;          /* Any protocol */
    hints.ai_flags = AI_CANONNAME;

    struct addrinfo *result;

    if (getaddrinfo(target_host, NULL, &hints, &result) != 0)
        printf("getaddrinfo failed: %s\n", strerror(errno));

    char ipstr[INET_ADDRSTRLEN];
    struct sockaddr_in *ipv4 = (struct sockaddr_in *)result->ai_addr;
    void *addr = &(ipv4->sin_addr);
    const char *str = inet_ntop(result->ai_family, addr, ipstr, sizeof(ipstr));

    printf("%s\n", str);
//    while (result)
//    {
//        printf("%s\n", result->ai_addr->sa_data);
//        result = result->ai_next;
//    }
}