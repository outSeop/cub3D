#include "cub3D.h"

int			main(int argc, char *argv[])
{
	t_game	game;

	prepare(&game, argc, argv);
	limit(&game);
	init_game(&game);
	load_textures(&game);
	start(&game);
}

void		prepare(t_game *game, int argc, char *argv[])
{
	int		fd;

	game->map.height = 0;
	if ((fd = error_input(argc, argv, &game->sc) == -1))
		print_error("ERROR - There is no file");
	char *a = malloc(1000);
	printf("!\n");
	printf("%zd\n", read(fd, a, 3));
	printf("=====\n");
	init_map(game);
	game->player.check = 0;
	if (parsing_cub(&game->map, fd) == -1)
		print_error("13");
	if (!(parsing_map(fd, &game->player, &game->map.height, &game->map)))
		print_error("23");
	if (!check_map(game->map.map_visited
		, (int)game->player.pos_x, (int)game->player.pos_y, game->map.height))
		print_error("map eeorr\n");
	error_file(&game->map);
	game->ray.width = game->map.resolution[0];
	game->ray.height = game->map.resolution[1];
	if (game->player.check != 1)
		print_error("ERROR - map is wrong");
}

void		limit(t_game *game)
{
	int x;
	int	y;

	mlx_get_screen_size(game->vars.mlx, &x, &y);
	if (game->ray.width > x)
		game->ray.width = x;
	if (game->ray.height > y)
		game->ray.height = y;
}
