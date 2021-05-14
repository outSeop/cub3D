#include "cub3D.h"

char			**free_all(char **line)
{
	int			i;

	i = 0;
	while (line[i])
	{
		free(line[i]);
		i++;
	}
	free(line);
	return (NULL);
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
