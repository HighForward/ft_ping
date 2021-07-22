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

enum V_Flags
{
    H_OPTION = 1 << 1, // binary 0001
    V_OPTION = 1 << 2, // binary 0010
//    NOTHING = 1 << 2, // binary 0100
//    NOTHING2 = 1 << 3  // binary 1000
};

enum N_Flags
{
    H_BIT = 1, // binary 0001
    V_BIT = 2, // binary 0010
//    NOTHING = 1 << 2, // binary 0100
//    NOTHING2 = 1 << 3  // binary 1000
};

typedef struct ICMP_pckt
{
    struct icmphdr hdr;
    char msg[PING_PACKET_SIZE - sizeof(struct icmphdr)];

} ICMP_pckt;

//typedef struct s_options
//{
//    int v_option;
//} t_options;

typedef struct s_ping
{
    struct ICMP_pckt send_pckt;
    char ip[INET_ADDRSTRLEN];
    int sockfd;
    char *dns_target;
    struct sockaddr_in addr_host;
    struct sockaddr_in addr_hit;
    int flag;

} t_ping_utility;

typedef struct s_rtt
{
    float min;
    float avg;
    float max;
    float mdev;
    int hops;
} t_rtt;

typedef struct s_stats
{
    int size_recv;
    int pck_send;
    int pck_recv;
    struct timeval begin_pgrm;
    struct timeval latest_pckt;

    struct timeval start;
    struct timeval time_elapsed;
    int pkt_replied;
    t_rtt rtt;
} t_stats;


void fill_icmp_packet(ICMP_pckt *ping_pkt);
unsigned short checksum(void *b, int len);

int parse_args(char **argv, char **dns_target, int *flag);
int resolve_dns(t_ping_utility *ping_base);
float get_average_of(float a, float b);
int is_integer(double N);
int ping_loop(t_ping_utility *ping_base, t_stats *stats);
int str_error(char *str, int code);
int send_data(t_stats *stats, t_ping_utility *ping_base);
int recv_data(unsigned char *buffer, t_stats *stats, t_ping_utility *ping_base);
void update_rtt_average(t_stats *stats);
void print_on_hops(ICMP_pckt *icmp_packet, struct ip ip_packet, t_stats *stats, t_ping_utility *ping_base);
void print_statistics(t_stats *stats, t_ping_utility *ping_base);
int toggle_flags(int flag);

void perform_h();

#endif