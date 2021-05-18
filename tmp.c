#include "cub3D.h"

void	save_res_info(t_map *map, char *line)
{
	int	i;

	if (!line[i])
	{
		printf("wrong\n");
		exit(-1);
	}
	map->resolution[0] = ft_atoi(line);
	while (line[i] && !ft_isspace(line[i]))
		i++;
	map->resolution[1] = ft_atoi(line + i);
}

void	set_draw_info(t_draw *draw, t_ray *ray)
{
		draw->line_height = (int)(ray->height / ray->perp_dist * 1.2);
		draw->draw_start = -(draw->line_height) / 2 + ray->height / 2;
		if (draw->draw_start < 0)
			draw->draw_start = 0;
		draw->draw_end = draw->line_height / 2 + ray->height / 2;
		if (draw->draw_end >= ray->height)
			draw->draw_end = ray->height - 1;
}

void	set_tex_info(t_game *game)
{
	game->tex.num = game->ray.direction;
	if (game->ray.side == 0)
		game->tex.wall_x = game->player.pos_y + game->ray.perp_dist * game->ray.dir_y;
	else
		game->tex.wall_x = game->player.pos_x + game->ray.perp_dist * game->ray.dir_x;
	game->tex.wall_x -= floor(game->tex.wall_x);
	game->tex.tex_x = (int)(game->tex.wall_x * (double)TEX_WIDTH);
	if (game->ray.side == 0 && game->ray.dir_x > 0)
		game->tex.tex_x = TEX_WIDTH - game->tex.tex_x - 1;
	if (game->ray.side == 1 && game->ray.dir_y < 0)
		game->tex.tex_x = TEX_WIDTH - game->tex.tex_x - 1;
	game->tex.step = 1.0 * TEX_HEIGHT / game->draw.line_height;
	game->tex.tex_pos = (game->draw.draw_start - game->ray.height / 2 + game->draw.line_height / 2);
	game->tex.tex_pos *= game->tex.step;
}

void	buffering_pixels(t_game *game, int pixel_x)
{
	int	i;
	int	color;

	i = 0;
	while (i < game->draw.draw_start)
		my_mlx_pixel_put(&game->stick, pixel_x, i++, game->map.celling);
	while (i < game->draw.draw_end)
	{
		game->tex.tex_y = (int)game->tex.tex_pos & (TEX_HEIGHT - 1);
		game->tex.tex_pos += game->tex.step;
		color = game->tex.tex[game->tex.num][TEX_HEIGHT * game->tex.tex_y + game->tex.tex_x];
		if (game->ray.side == 1)
			color = (color >> 1) & 0x007f7f7f;
		my_mlx_pixel_put(&game->stick, pixel_x, i, color);
		i++;
	}
	while (i < game->ray.height)
		my_mlx_pixel_put(&game->stick, pixel_x, i++, game->map.floor);
}






int			check_map(char **map, int x, int y, int map_height)
{
	int		i;
	t_node	*node_x;
	t_node	*node_y;

	node_x = create_node();
	node_y = create_node();
	add_nodes(node_y, node_x, y, x);
	if (!bfs(node_y, node_x, map, map_height))
		return (0);
	while (find_zero(map, &y, &x))
	{
		map[y][x] = add_nodes(node_y, node_x, y, x);
		if (!bfs(node_y, node_x, map, map_height))
			return (0);
	}
	return (1);
}

char		add_nodes(t_node *ny, t_node *nx, int y, int x)
{
	add_node(ny, y);
	add_node(nx, x);
	return ('1');
}

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
			if (y < 0 || y > map_height || x < 0 || x >= ft_strlen(map[y]))
				return (0);
			if (map[y][x] == '1')
				continue;
			map[y][x] = add_nodes(node_y, node_x, y, x);;
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
