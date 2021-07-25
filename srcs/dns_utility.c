#include "../includes/ft_ping.h"

void reverse_dns_lookup(t_ping_utility *ping_base, char *hit_ip)
{
    struct sockaddr_in sa;
    socklen_t len;
    char hbuf[NI_MAXHOST];

    memset(&sa, 0, sizeof(struct sockaddr_in));

    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = inet_addr(hit_ip);
    len = sizeof(struct sockaddr_in);

    if (getnameinfo((struct sockaddr *) &sa, len, hbuf, sizeof(hbuf),NULL, 0, NI_NAMEREQD))
        memset(ping_base->fqdn, 0, sizeof(ping_base->fqdn));
    else
    {
        int i = 0;
        while (hbuf[i])
        {
            ping_base->fqdn[i] = hbuf[i];
            i++;
        }
        ping_base->fqdn[i] = '\0';
    }
}

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
