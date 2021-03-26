#include "cub3D.h"

void	save_res_info(t_map *map, char *line)
{
	int	i;

	map->resolution[0] = ft_atoi(line);
	while (!ft_isspace(line[i]))
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
	//game->tex.num = game->map.map[game->ray.map_x][game->ray.map_y] - 48 - 1;
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
		color = g_texture[game->tex.num][TEX_HEIGHT * game->tex.tex_y + game->tex.tex_x];
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
	t_node	*node_x;
	t_node	*node_y;
	int		hy[4] = {0, 0, 1, -1};
	int		hx[4] = {1, -1, 0, 0};
	char	**visited;

	visited = malloc(sizeof(map));
	ft_memcpy(visited, map, sizeof(map));
	node_x = create_node();
	node_y = create_node();

	add_node(node_x, x);
	add_node(node_y, y);

	while (node_y)
	{
		for (int i = 0; i < 4; i++)
		{
			int cy = node_y->y + hy[i];
			int cx = node_x->y + hx[i];

			if (cy < 0 || cy > map_height || cx < 0 || cx > ft_strlen(map[x]))
				return (0);
			if (map[cy][cx] != 1 && visited[cy][cx] != 1)
			{
				visited[cy][cx] = 1;
				add_node(node_y, cy);
				add_node(node_x, cx);
			}
		}
		node_y = node_y->next;
		node_x = node_x->next;
	}

}
