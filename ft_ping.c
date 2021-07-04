#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/ip_icmp.h>
#include <errno.h>
#include <time.h>
#include <fcntl.h>
#include <signal.h>
#include <time.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#define PING_PACKET_SIZE 64
int errno;

struct ping_pkt
{
    struct icmphdr hdr;
    char msg[PING_PACKET_SIZE - sizeof(struct icmphdr)];
};

int str_error(char *str, int code)
{
    printf("%s\n", str);
    return (code);
}

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

void fill_icmp_packet(struct ping_pkt *ping_pkt)
{
    int i;

    bzero(ping_pkt, sizeof(struct ping_pkt));
    (*ping_pkt).hdr.type = ICMP_ECHO;
    (*ping_pkt).hdr.code = 0;
    (*ping_pkt).hdr.un.echo.id = getpid();
    (*ping_pkt).hdr.un.echo.sequence++;

    for (i = 0; i < sizeof((*ping_pkt).msg) - 1; i++)
        (*ping_pkt).msg[i] = (char)(i + '0');
    (*ping_pkt).msg[i] = 0;

    (*ping_pkt).hdr.checksum = checksum(&(*ping_pkt), sizeof((*ping_pkt)));
}

int create_socket(int *sockfd)
{
    int ttl = 64;
    struct timeval tv_out;

    tv_out.tv_sec = 1;
    tv_out.tv_usec = 0;

    (*sockfd) = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);

    if ((*sockfd) < 0)
        return str_error("Socket file descriptor not received!", -1);

    if (setsockopt((*sockfd), SOL_IP, IP_TTL, &ttl, sizeof(ttl)) != 0)
        return str_error("Setting socket options to TTL failed!", -1);
    if (setsockopt((*sockfd), SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv_out, sizeof(tv_out)) != 0)
        return str_error("Setting socket timeout option failed!", -1);

    return (1);
}

struct sockaddr_in resolve_dns(char *target_host)
{
    struct hostent *host_entity;
    struct sockaddr_in addr_host;
    bzero(&addr_host, sizeof(struct sockaddr_in));

    printf("Resolving DNS..\n");
    if ((host_entity = gethostbyname(target_host)) == NULL)
    {
        str_error("gethostbyname: error", 1);
        exit(1);
    }

    char *ip = (char*)malloc(NI_MAXHOST * sizeof(char));
    strcpy(ip, inet_ntoa(*(struct in_addr *)host_entity->h_addr));
    printf("ip: %s\n", ip);

    addr_host.sin_family = host_entity->h_addrtype;
    addr_host.sin_port = htons (0);
    addr_host.sin_addr.s_addr  = *(long*)host_entity->h_addr;
    return (addr_host);
}

int main(int argc, char **argv)
{
    char *dns_target = "google.com";
    struct sockaddr_in addr_host;
    struct ping_pkt pckt;
    unsigned char *pktrecv;
    int sockfd;
    
    addr_host = resolve_dns(dns_target);
    pktrecv = (unsigned char *) malloc (sizeof(struct ip) + sizeof(struct ping_pkt));

    if (create_socket(&sockfd) < 0)
        return (-1);

    int STOP = 0;
    struct sockaddr_in r_addr;
    unsigned int addr_len = sizeof(r_addr);
    struct ping_pkt *tmp;

    while (!STOP)
    {
        fill_icmp_packet(&pckt);

        if (sendto(sockfd, &pckt, sizeof(pckt), 0, (struct sockaddr *) &addr_host, sizeof(struct sockaddr)) < 0)
            return str_error(strerror(errno), 1);

        usleep(1000000);

        if (recvfrom(sockfd, pktrecv, sizeof(struct ip) + sizeof(struct ping_pkt), 0, (struct sockaddr *) &r_addr, &addr_len) < 0)
            return str_error(strerror(errno), 1);

        tmp = (struct ping_pkt *) (pktrecv + sizeof(struct ip));

        printf("%d bytes from %s (h: %s) (%s) msg_seq=%d ttl=%d rtt = %d ms.\n", PING_PACKET_SIZE, dns_target,
               dns_target, dns_target, 0, 64, 0);

    }

}