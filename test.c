#include <stdio.h>
#include "cub3D.h"
#include "libft/libft.h"
#include <unistd.h>


int			main(int argc, char *argv[])
{
	t_game 	game;
	int		i;
	int		fd;

	if ((fd = error_input(argc, argv)) == -1)
		return (0);
	init_map(&game);
	init_player(&game);
	if (parsing_cub(&game.map, &game.player, fd) == -1)
		print_error("1");
	if (!(parsing_map(fd, &game.player, &game.map.height, &game.map)))
		print_error("2");
	if (!check_map(game.map.map_visited, (int)game.player.pos_x, (int)game.player.pos_y, game.map.height))
		error_file(&game.map);
	game.ray.width = game.map.resolution[0];
	game.ray.height = game.map.resolution[1];
	init_game(&game);
	if (game.player.check != 1)
	{
		printf("ERROR\n");
		return (0);
	}

	load_textures(&game);
	//engine(&game);
	start(&game);
}
