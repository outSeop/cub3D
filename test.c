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
	init_map(&game);
	init_player(&game);
	parsing_cub(&game.map, &game.player, fd);
	check_map(game.map.map, (int)game.player.pos_x, (int)game.player.pos_y, game.map.height);
	game.ray.width = game.map.resolution[0];
	game.ray.height = game.map.resolution[1];
	init_game(&game);
	game.z_buffer = malloc(sizeof(double) * (game.ray.width + 1));
	game.draw_buffer = malloc(sizeof(int) * game.ray.width * game.ray.height );
	if (game.player.check != 1)
	{
		printf("ERROR\n");
		return (0);
	}

	load_textures(&game);
	engine(&game);
	start(&game);
}
