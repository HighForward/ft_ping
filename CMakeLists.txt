cmake_minimum_required(VERSION 3.16)
project(ping C)

set(CMAKE_C_STANDARD 11)

add_executable(ping srcs/ft_ping.c srcs/rtt_utility.c srcs/dns_utility.c srcs/statistics.c srcs/icmp_packet.c)
