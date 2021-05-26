#include "cub3D.h"

void			reset(t_game *game)
{
	free(game->z_buffer);
	free_sprite(game->sprite);
	init_stick(game);
	reset_map(&game->map);
}

void			reset_map(t_map *map)
{
	int			i;
	int			j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (map->map[i][j])
		{
			if (map->map[i][j] == '3')
				map->map[i][j] = '2';
			j++;
		}
		i++;
	}
}
