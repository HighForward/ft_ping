#include "../includes/ft_ping.h"

int STOP = 0;

void intHandler(int sig) {
    STOP = 1;
    write(1, "\n", 1);
}

int str_error(char *str, int code)
{
    printf("%s\n", str);
    return (code);
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

int main(int argc, char **argv)
{
    char *dns_target = argv[1];
    struct sockaddr_in addr_host;
    ICMP_pckt pckt;
    ICMP_pckt *tmp;
    unsigned char *pktrecv;
    char *ip;
    int sockfd;
    int nb_pckt_send = 0;
    int nb_pckt_recv = 0;

    signal(SIGINT, intHandler);

    if (create_socket(&sockfd) < 0)
        return (-1);

    ip = malloc(sizeof(char) * INET_ADDRSTRLEN + 5);
    pktrecv = (unsigned char *) malloc (sizeof(struct ip) + sizeof(ICMP_pckt));
    addr_host = resolve_dns(dns_target, &ip);

    struct sockaddr_in r_addr;
    unsigned int addr_len = sizeof(r_addr);
    int reicvd_pkt;
    struct timeval start;
    struct timeval time_elapsed;

    printf("PING %s (%s) %lu(%lu) bytes of data\n", dns_target, ip, sizeof(ICMP_pckt), sizeof(ICMP_pckt) + sizeof(struct ip));

    gettimeofday(&start, NULL);
    while (!STOP)
    {
        reicvd_pkt = 0;
        gettimeofday(&start, NULL);
        fill_icmp_packet(&pckt);

        if (sendto(sockfd, &pckt, sizeof(pckt), 0, (struct sockaddr *) &addr_host, sizeof(struct sockaddr)) < 0)
            return str_error(strerror(errno), 1);

        nb_pckt_send++;
        if (recvfrom(sockfd, pktrecv, sizeof(struct ip) + sizeof(ICMP_pckt), 0, (struct sockaddr *) &r_addr, &addr_len) >= 0)
        {
            nb_pckt_recv++;
            reicvd_pkt = 1;
        }

        if (!STOP && reicvd_pkt)
        {
            gettimeofday(&time_elapsed, NULL);
            tmp = (ICMP_pckt *) (pktrecv + sizeof(struct ip));

            printf("%lu bytes from %s (%s): icmp_seq=%d ttl=%d time=%.1f ms\n", sizeof(ICMP_pckt) , dns_target,
                   ip, tmp->hdr.un.echo.sequence, 64,
                   (float) (((float) time_elapsed.tv_usec - (float) start.tv_usec) / 1000));
            usleep(1000000);
        }
    }

    gettimeofday(&time_elapsed, NULL);
    printf("--- %s ping statistics ---\n", dns_target);

    float average_loss = get_average_of(nb_pckt_send, nb_pckt_recv);
    int type = is_integer(average_loss);
    printf("%d packets transmitted, %d received, %.*f%% packets lost, time %ld\n", nb_pckt_send, nb_pckt_recv, (type == 0 ? 4 : 0), average_loss, (time_elapsed.tv_usec - start.tv_usec) / 1000);
}