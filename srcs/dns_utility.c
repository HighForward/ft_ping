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

//    const char *str = inet_ntop(result->ai_family, result->ai_addr, (*ip), result->ai_addrlen);

//    printf("%s\n", str);
    printf("%s\n", result->ai_canonname);
}