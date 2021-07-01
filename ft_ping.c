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
#include <time.h>
#include <fcntl.h>
#include <signal.h>
#include <time.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#define PING_PKT_SIZE 64

struct ping_pkt
{
    struct icmphdr hdr;
    char msg[PING_PKT_SIZE - sizeof(struct icmphdr)];
};

struct ping_pkt fill_icmp_packet();
int str_error(char *str, int code)
{
    printf("%s\n", str);
    return (code);
}

unsigned short checksum(void *b, int len)
{
    unsigned short *buf = b;
    unsigned int sum=0;
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

struct ping_pkt fill_icmp_packet()
{
    struct ping_pkt result;

    int i = 0;

    bzero(&result, sizeof(struct ping_pkt));
    result.hdr.type = ICMP_ECHO;
    result.hdr.code = 0;
    result.hdr.un.echo.id = getpid();

    for (i = 0; i < sizeof(result.msg) - 1; i++)
        result.msg[i] = i + '0';
    result.msg[i] = 0;

    result.hdr.un.echo.sequence = 0;
    result.hdr.checksum = checksum(&result, sizeof(result));

    return (result);
}

int create_socket()
{
    int ttl = 64;
    struct timeval tv_out;

    tv_out.tv_sec = 1;
    tv_out.tv_usec = 0;

    int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);

    if (sockfd < 0)
        return str_error("Socket file descriptor not received!", -1);

    if (setsockopt(sockfd, SOL_IP, IP_TTL, &ttl, sizeof(ttl)) != 0)
        return str_error("Setting socket optionsto TTL failed!", -1);
    if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv_out, sizeof(tv_out)) != 0)
        return str_error("Setting socket timeout option failed!", -1);

    return (sockfd);
}

int main(int argc, char **argv)
{

    struct ping_pkt pckt;
    int sockfd;
    char *dns_target = "google.com";

    struct hostent *host_entity;
    struct sockaddr_in addr_host;

    printf("\nResolving DNS..\n");
    if ((host_entity = gethostbyname(dns_target)) == NULL)
        return str_error("gethostbyname: error", 1);

    char *ip = (char*)malloc(NI_MAXHOST * sizeof(char));
    strcpy(ip, inet_ntoa(*(struct in_addr *)host_entity->h_addr));
    printf("ip: %s\n", ip);

    addr_host.sin_family = host_entity->h_addrtype;
    addr_host.sin_port = htons (0);
    addr_host.sin_addr.s_addr  = *(long*)host_entity->h_addr;

    if ((sockfd = create_socket()) < 0)
        return (sockfd);

    pckt = fill_icmp_packet();

    usleep(1000000);

    int ret = 0;
    if ((ret = sendto(sockfd, &pckt, sizeof(pckt), 0, (struct sockaddr*) &addr_host, sizeof(struct sockaddr))) <= 0)
        printf("\nPacket Sending Failed! %d\n", ret);

    struct sockaddr_in r_addr;
    int addr_len = sizeof(r_addr);

    if (recvfrom(sockfd, &pckt, sizeof(pckt), 0, (struct sockaddr*)&r_addr, &addr_len) <= 0)
        printf("\nPacket receive failed!\n");
    else
        printf("%d bytes from %s (h: %s) (%s) msg_seq=%d ttl=%d rtt = %d ms.\n",PING_PKT_SIZE, dns_target, dns_target, dns_target, 0, 64, 0);

}