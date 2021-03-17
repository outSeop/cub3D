#include "cub3D.h"

void		jump(t_game *game)
{
	int		i;

	i = 0;
	while (i < game->ray.height / 2)
	{
		game->player.jump = i;
		engine(game);
		i++;
	}
}

