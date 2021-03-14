#include <stdio.h>
#include "cub3D.h"
#include "libft/libft.h"
#include <unistd.h>


int			main(int argc, char *argv[])
{
	t_game 	game;
	int		fd;

	if (argc != 2)
	{
		printf("ERROR\n");
		return (0);
	}
	fd = open(argv[1], O_RDONLY);
	init_game(&game);
	parsing_cub(&game.map, &game.player, fd);

	for (int i = 0; i < 5; i++)
		printf("%s\n", game.map.textures[i]);
	printf("%X\n", game.map.floor);
	printf("%X\n", game.map.celling);
	int i = 0;
	while (game.map.map[i])
	{
		printf("%s\n", game.map.map[i]);
		i++;
	}
	printf("%2f - %.2f\n", game.player.pos_x, game.player.pos_y);
	printf("%2f - %.2f\n", game.player.dir_x, game.player.dir_y);

	make_texture();
	engine(&game);
	start(&game);
}
