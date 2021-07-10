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
int STOP;

typedef struct ICMP_pckt
{
    struct icmphdr hdr;
    char msg[PING_PACKET_SIZE - sizeof(struct icmphdr)];
} ICMP_pckt;

typedef struct s_stats
{
    size_t size_recv;
    int pck_send;
    int pck_recv;
    struct timeval start;
    struct timeval time_elapsed;
    int pkt_replied;
} t_stats;


void fill_icmp_packet(ICMP_pckt *ping_pkt);
unsigned short checksum(void *b, int len);

int resolve_dns(char *target_host, struct sockaddr_in *addr_host,char **ip);
float get_average_of(float a, float b);
int is_integer(double N);
int ping_loop(int sockfd, char *target_host, struct sockaddr_in *addr_host, char *ip, t_stats *stats);
int str_error(char *str, int code);
int send_data(int sockfd, ICMP_pckt *pckt, t_stats *stats, struct sockaddr_in *addr_host);
int recv_data(int sockfd, unsigned char *buffer, t_stats *stats, struct sockaddr_in *addr_host);

#endif