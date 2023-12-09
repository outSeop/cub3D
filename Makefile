.PHONY: libft minilibx all clean fclean re

SRCS =	action.c \
		bitmap.c \
		find_player.c \
		check_element.c \
		sprite.c \
		tmp.c \
		node.c \
		init.c	\
		main.c	\
		engine.c \
		gnl/get_next_line.c \
		gnl/get_next_line_utils.c \
		parsing.c \
		game.c \
		error.c \
		utils.c \
		check_invalid_map.c \
		set_parsing_info.c \
		calculate.c \
		reset.c \
		free.c \

NAME = Cub3D
GCC_FLAG = -Wall -Werror -Wextra
CC = gcc $(GCC_FLAG)

OBJS = $(SRCS:.c=.o)

all: libft minilibx $(NAME)

libft:
	make -C libft/

minilibx:
	make -C mlx

$(%.o): $(%.c)
	$(CC) -o $@ -c $^

$(NAME): $(OBJS)
	$(CC) -o $@ $^ -Lmlx -lmlx -framework OPENGL -framework Appkit -Llibft -lft


clean:
	rm -f $(OBJS)
	make -C libft/ clean
	make -C mlx clean

fclean: clean
	rm -f $(NAME)
	make -C libft/ fclean
	make -C mlx clean

re: fclean all
