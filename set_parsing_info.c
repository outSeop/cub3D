#include "cub3D.h"

void		save_res_info(t_map *map, char *line)
{
	int		i;
	char	**lines;

	if (line[0] == '\0')
		print_error("ERROR 6\n");
	lines = ft_split(line, ' ');
	i = 0;
	while (line[i])
	{
		if (!ft_isdigit(line[i]) && line[i] != ' ')
			print_error("ERROR 5\n");
		i++;
	}
	i = 0;
	while (lines[i])
		i++;
	if (i != 2)
		print_error("ERROR 4\n");
	map->resolution[0] = ft_atoi(lines[0]);
	map->resolution[1] = ft_atoi(lines[1]);
	free_all(lines);
}

int			check_map(char **map, int x, int y, int map_height)
{
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
			print_error("ERROR - map error\n");
	}
	free_node(node_x);
	free_node(node_y);
	return (1);
}

void		make_texture(t_game *game, int i)
{
	int		y;
	int		x;
	t_stick	*s;

	s = &game->stick;
	s->img = mlx_xpm_file_to_image(game->vars.mlx, game->map.textures[i]
		, &s->width, &s->height);
	s->addr = (int*)mlx_get_data_addr(s->img, &s->bits_per_pixel
		, &s->line_length, &s->endian);
	game->tex.tex[i] = malloc(sizeof(int) * s->width * s->height);
	game->tex.tex_height[i] = s->height;
	game->tex.tex_width[i] = s->width;
	if (s->img == 0)
		print_error("ERROR - Wrong xpm file");
	mlx_put_image_to_window(game->vars.mlx, game->vars.win, s->img, 0, 0);
	y = -1;
	while (++y < s->height)
	{
		x = -1;
		while (++x < s->width)
			game->tex.tex[i][s->width * y + x] = s->addr[s->width * y + x];
	}
	init_stick(game);
}

void		load_textures(t_game *game)
{
	int		i;

	i = 0;
	while (i < 5)
		make_texture(game, i++);
}
