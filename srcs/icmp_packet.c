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
//        printf("send error: ");
//        return str_error(strerror(errno), 1);
        exit(1);
    }
    stats->pck_send++;
    return (0);
}

int recv_data(unsigned char *buffer, t_stats *stats, t_ping_utility *ping_base)
{
    struct msghdr msg;
    struct iovec   iov;
    ft_bzero(&msg, sizeof(struct msghdr));
    ft_bzero(&iov, sizeof(struct iovec));

    struct sockaddr_in tmp;
    memcpy(&tmp, &ping_base->addr_host, sizeof(struct sockaddr_in));

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

    if ((stats->size_recv = recvmsg(ping_base->sockfd, &msg, 0)) >= 0)
    {
        stats->pck_recv++;
        stats->pkt_replied = 1;
        ping_base->addr_hit = tmp;
    }

    memcpy(buffer, tmp_buffer, (sizeof(struct ip) + 4 + sizeof(struct ip) + sizeof(struct ICMP_pckt)));

    return (0);
}