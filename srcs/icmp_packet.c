#include "../includes/ft_ping.h"

unsigned short checksum(void *b, int len)
{
    unsigned short *buf = b;
    unsigned int sum = 0;
    unsigned short result;

    for ( sum = 0; len > 1; len -= 2 )
        sum += *buf++;

    if ( len == 1 )
        sum += *(unsigned char*)buf;

    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += (sum >> 16);
    result = ~sum;
    return (result);
}

void fill_icmp_packet(ICMP_pckt *ping_pkt)
{
    int i;

    (*ping_pkt).hdr.type = ICMP_ECHO;
    (*ping_pkt).hdr.code = 0;
    (*ping_pkt).hdr.un.echo.id = getpid();
    (*ping_pkt).hdr.un.echo.sequence++;

    for (i = 0; i < sizeof((*ping_pkt).msg) - 1; i++)
        (*ping_pkt).msg[i] = (char)(i + '0');
    (*ping_pkt).msg[i] = 0;

    (*ping_pkt).hdr.checksum = 0;
    (*ping_pkt).hdr.checksum = checksum(&(*ping_pkt), sizeof((*ping_pkt)));
}

int send_data(t_stats *stats, t_ping_utility *ping_base)
{
    stats->pkt_replied = 0;
    fill_icmp_packet(&ping_base->send_pckt);

    if (sendto(ping_base->sockfd, &ping_base->send_pckt, sizeof(ICMP_pckt), 0, (struct sockaddr *)&ping_base->addr_host, sizeof(struct sockaddr)) < 0)
    {
        printf("connect: Invalid argument\n");
        exit(1);
    }

//    printf("----------\ntype: %d\ncode: %d\nchecksum: %d\nid: %d\nsequence: %d\n----------\n",
//           ping_base->send_pckt.hdr.type, ping_base->send_pckt.hdr.code, ping_base->send_pckt.hdr.checksum, ping_base->send_pckt.hdr.un.echo.id, ping_base->send_pckt.hdr.un.echo.sequence);

    stats->pck_send++;
    return (0);
}

int compare_packet(const struct ICMP_pckt *p1, const struct ICMP_pckt *p2)
{
    if (p1->hdr.type == p2->hdr.type &&
            p1->hdr.code == p2->hdr.code &&
            p1->hdr.checksum == p2->hdr.checksum &&
            p1->hdr.un.echo.id == p2->hdr.un.echo.id &&
            p1->hdr.un.echo.sequence == p2->hdr.un.echo.sequence)
        return (1);
    return (0);
}

int is_loopback_ip(t_ping_utility *ping_base)
{
    if (ft_strlen(ping_base->dns_target) > 3 && (ft_strncmp("127", ping_base->dns_target, 3) == 0 || (ft_strncmp("localhost", ping_base->dns_target, 9) == 0)))
            return (1);
    return (0);
}

int cancel_loopback(t_ping_utility *ping_base, unsigned char *tmp_buffer)
{
    struct ICMP_pckt *tmp_icmp;
    tmp_icmp = (ICMP_pckt *) (tmp_buffer + sizeof(struct ip));

    if (is_loopback_ip(ping_base) && compare_packet(&ping_base->send_pckt, tmp_icmp))
        return (1);
    return (0);
}

int recv_data(unsigned char *buffer, t_stats *stats, t_ping_utility *ping_base)
{
    struct msghdr msg;
    struct iovec   iov;
    ft_bzero(&msg, sizeof(struct msghdr));
    ft_bzero(&iov, sizeof(struct iovec));

    struct sockaddr_in tmp;
    unsigned char tmp_buffer[(sizeof(struct ip) + 4 + sizeof(struct ip) + sizeof(struct ICMP_pckt))];
    bzero(tmp_buffer, sizeof(tmp_buffer));

    iov.iov_base = tmp_buffer;
    iov.iov_len = (sizeof(struct ip) + 4 + sizeof(struct ip) + sizeof(struct ICMP_pckt));
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;
    msg.msg_name = &tmp;
    msg.msg_namelen = sizeof(struct sockaddr_in);
    msg.msg_control = NULL;
    msg.msg_controllen = 0;
    msg.msg_flags = 0;

    int x = 1;
    do
    {
        if ((stats->size_recv = recvmsg(ping_base->sockfd, &msg, 0)) >= 0)
        {
            if (cancel_loopback(ping_base, tmp_buffer))
                continue;

            stats->pck_recv++;
            stats->pkt_replied = 1;
            if (ping_base->addr_hit.sin_addr.s_addr == 0)
            {
                ping_base->addr_hit = tmp;
                inet_ntop(ping_base->addr_hit.sin_family, &ping_base->addr_hit.sin_addr, ping_base->hit_ip, INET_ADDRSTRLEN);
                reverse_dns_lookup(ping_base, ping_base->hit_ip);

            }
        }
        x--;
    } while (x != 0);

    memcpy(buffer, tmp_buffer, (sizeof(struct ip) + 4 + sizeof(struct ip) + sizeof(struct ICMP_pckt)));

    return (0);
}