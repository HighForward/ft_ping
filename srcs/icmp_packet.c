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

int send_data(int sockfd, ICMP_pckt *pckt, t_stats *stats, struct sockaddr_in *addr_host)
{
    stats->pkt_replied = 0;
    fill_icmp_packet(pckt);

    if (sendto(sockfd, pckt, sizeof(*pckt), 0, (struct sockaddr *)addr_host, sizeof(struct sockaddr)) < 0)
        return str_error(strerror(errno), 1);

    stats->pck_send++;
    return (0);
}

int recv_data(int sockfd, unsigned char *buffer, t_stats *stats, struct sockaddr_in *addr_host)
{
    struct msghdr msg;
    struct iovec   iov;
    bzero(&msg, sizeof(struct msghdr));
    bzero(&iov, sizeof(struct iovec));

    iov.iov_base = buffer;
    iov.iov_len = sizeof(ICMP_pckt) + sizeof(struct ip);
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;
    msg.msg_name = (void*)addr_host;
    msg.msg_namelen = sizeof(*addr_host);
    msg.msg_control = NULL;
    msg.msg_controllen = 0;
    msg.msg_flags = 0;

    if ((stats->size_recv = recvmsg(sockfd, &msg, 0)) >= 0)
    {
        stats->pck_recv++;
        stats->pkt_replied = 1;
    }
    return (0);
}