#COLORS
GREEN		= \033[0;32m
RED 		= \033[0;31m
BOLD		= \033[1m
NORMAL		= \033[0m
UP 			= \033[A
CUT 		= \033[K

SRCS = $(wildcard srcs/*.c) $(wildcard srcs/parsing/*.c) $(wildcard srcs/utils/*.c) $(wildcard srcs/math/*.c)

OBJDIR	:= objs
OBJS	:= $(addprefix $(OBJDIR)/, ${SRCS:.c=.o})

NAME	= miniRT

CC		= gcc -g
RM		= rm -f

CFLAGS 	= -Wall -Wextra -Werror #-fsanitize=address

all:		${NAME}

$(OBJDIR)/%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -Ilibft -I./mlx -c $< -o $@

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
			@${RM} -r ${OBJDIR}

fclean:		clean
			@${RM} ${NAME}

re:			fclean all

.PHONY:		libft all bonus clean fclean re
