#include "cub3D.h"

int			bfs(t_node *node_y, t_node *node_x, char **map, int map_height)
{
	int		y;
	int		x;
	int		i;

	while (node_y->next)
	{
		i = -1;
		while (++i < 4)
		{
			y = node_y->next->y + HY[i] - '0' - 2;
			x = node_x->next->y + HX[i] - '0' - 2;
			if (y < 0 || y > map_height || x < 0 || x >= (int)ft_strlen(map[y])
				|| map[y][x] == ' ')
			{
				return (0);
			}
			if (map[y][x] == '1')
				continue;
			map[y][x] = add_nodes(node_y, node_x, y, x);
		}
		node_y = node_y->next;
		node_x = node_x->next;
	}
	return (1);
}

int			find_zero(char **map, int *y, int *x)
{
	int		i;
	int		j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0')
			{
				*y = i;
				*x = j;
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

char		add_nodes(t_node *ny, t_node *nx, int y, int x)
{
	add_node(ny, y);
	add_node(nx, x);
	return ('1');
}
