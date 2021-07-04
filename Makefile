SRCS		=	./ft_ping.c ./rtt_utility.c

NAME		=	ft_ping

#H           =   ../includes/push_swap.h

OBJS		=	${SRCS:.c=.o}

FLAGS		=	-Iincludes

CC			=	gcc

RM			=	rm -f

.c.o:
				@$(CC) $(FLAGS) -c $< -o ${<:.c=.o}

all: ${NAME}

#link:
				@#$(MAKE) -C ../libft/

#${NAME}: ${OBJS} ${H} link
${NAME}: ${OBJS}
			    @$(CC) ${OBJS} -Wall -Wextra -Werror -o ${NAME}
			    @echo "\033[1;32m > Building <\033[0m\033[1;35m .o files\033[0m"
			    @echo "\033[1;32m > Building <\033[0m\033[1;36m ${NAME}\033[0m"

clean:
				@${RM} ${OBJS}
				@$(MAKE) clean
				@echo "\033[1;31m > Deleting <\033[0m\033[1;35m .o files\033[0m"

fclean: clean
			    @${RM} $(NAME)
			    @$(MAKE) fclean
			    @echo "\033[1;31m > Deleting <\033[0m\033[1;35m ${NAME} \033[0m"

re:	fclean all

.PHONY: clean fclean re bonus run