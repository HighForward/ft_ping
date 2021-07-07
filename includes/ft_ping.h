#ifndef FT_PING
#define FT_PING

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
#include <signal.h>
#include <sys/time.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#define PING_PACKET_SIZE 56

int errno;

typedef struct ICMP_pckt
{
    struct icmphdr hdr;
    char msg[PING_PACKET_SIZE - sizeof(struct icmphdr)];
} ICMP_pckt;

typedef struct s_stats
{
    int pck_send;
    int pck_recv;
    struct timeval start;
    struct timeval time_elapsed;
    int pkt_replied;
    struct sockaddr_in r_addr;
    unsigned int r_addr_len;
} t_stats;


void fill_icmp_packet(ICMP_pckt *ping_pkt);
unsigned short checksum(void *b, int len);

struct sockaddr_in resolve_dns(char *target_host, char **ip);
float get_average_of(float a, float b);
int is_integer(double N);


#endif