.PHONY: libft minilibx all clean fclean re

SRCS =	init_color.c \
		main.c	\
		init.c	\
		engine.c \
		hooks.c \
		texture.c \
		actions.c \
		gnl/get_next_line.c \
		gnl/get_next_line_utils.c \

NAME = Cub3D
GCC_FLAG =  -g -fsanitize=address
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
