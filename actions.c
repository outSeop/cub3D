#include "cub3D.h"

void		jump(t_game *game)
{
	int		i;

	i = 0;
	while (i < HEIGHT / 2)
	{
		game->player.jump = i;
		engine(game);
		i++;
	}
}

