#COLORS
GREEN		= \033[0;32m
RED 		= \033[0;31m
BOLD		= \033[1m
NORMAL		= \033[0m
UP 			= \033[A
CUT 		= \033[K

SRCS = $(wildcard srcs/*.c)

OBJS	:= ${SRCS:.c=.o}

NAME	= miniRT

CC		= gcc -g
RM		= rm -f

CFLAGS 	= -Wall -Wextra -Werror #-fsanitize=address

all:		${NAME}

%.o:	%.c
		@${CC} ${CFLAGS} -Ilibft -I./mlx -c $? -o $@

${NAME}:	${OBJS}
		@$(MAKE) -C libft
		@$(MAKE) -C mlx
		${CC} ${CFLAGS} $^ -Llibft -lft -L./mlx -lmlx -framework OpenGL -framework AppKit -o ${NAME}
		@echo "$(GREEN)[$(BOLD)OK$(NORMAL)$(GREEN)]$(NORMAL) $(BOLD)$(NAME)$(NORMAL) is ready"

libft:
		make -C libft

mlx:
		make -C mlx

clean:
			make clean -C libft
			make clean -C mlx
			@${RM} ${OBJS}

fclean:		clean
			@${RM} ${NAME}

re:			fclean all

.PHONY:		libft all bonus clean fclean re
