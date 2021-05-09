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
		return (0);
	game.map.map = parsing_map(fd, &game.player, &game.map.height);
	check_map(game.map.map, (int)game.player.pos_x, (int)game.player.pos_y, game.map.height);
	game.ray.width = game.map.resolution[0];
	game.ray.height = game.map.resolution[1];
	game.map.map_s = (int**)malloc(sizeof(int*) * game.map.height);
	i = 0;
	while (i < game.map.height)
	{
		game.ray.map_size += ft_strlen(game.map.map[i]);
		game.map.map_s[i] = malloc(sizeof(int) * ft_strlen(game.map.map[i]));
		i++;
	}
	// ft_memset(game.map.map_s, 0, game.ray.map_size);
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
