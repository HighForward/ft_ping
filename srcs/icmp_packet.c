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
