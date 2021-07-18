SRCS		=	./srcs/ft_ping.c ./srcs/rtt_utility.c ./srcs/dns_utility.c ./srcs/statistics.c ./srcs/icmp_packet.c ./srcs/loop.c ./srcs/output.c ./srcs/args.c ./srcs/flags.c

NAME		=	ft_ping

H           =   ./includes/ft_ping.h

OBJS_DIR	= ./objects/
OBJS		= ${SRCS:%.c=${OBJS_DIR}/%.o}

FLAGS		=	-Iincludes

CC			=	gcc

RM			=	rm -f

${OBJS_DIR}/%.o: %.c
				@mkdir -p ${@D}
				@${CC} ${CFLAGS} -c $< -o $@

all: ${NAME}

#link:
				@#$(MAKE) -C ../libft/

${NAME}: ${OBJS} ${H}
			    @$(CC) ${OBJS} -Wall -Wextra -Werror -o ${NAME}
			    @echo "\033[1;32m > Building <\033[0m\033[1;36m ${NAME}\033[0m"

clean:
				@${RM} ${OBJS}
				@echo "\033[1;31m > Deleting <\033[0m\033[1;35m .o files\033[0m"

fclean: clean
			    @${RM} $(NAME)
			    @echo "\033[1;31m > Deleting <\033[0m\033[1;35m ${NAME} \033[0m"

re:	fclean all

.PHONY: clean fclean re bonus run