#include "cub3D.h"

void			prepare(t_game *game, int argc, char *argv[])
{
	base(game, argc, argv);
	parse(game);
	check(game);
	error(game);
	set(game);
}

void			parse(t_game *game)
{
	parsing_info(game->info);
	parsing_map(game->map, game->player);
}

void			check(t_game *game)
{
	check_map(game->map, game->player);
}
