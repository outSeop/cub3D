/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_parsing_info.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inssong <inssong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 05:04:26 by inssong           #+#    #+#             */
/*   Updated: 2021/05/27 08:28:26 by inssong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void		save_res_info(t_map *map, char *line)
{
	int		i;
	char	**lines;

	map->chk_dp[R]++;
	if (map->chk_dp[R] > 1)
		print_error("ERROR -  Duplicate Resolusion");
	if (line[0] == '\0')
		print_error("ERROR - There is no resolution info");
	lines = ft_split(line, ' ');
	i = 0;
	while (line[i])
	{
		if (!ft_isdigit(line[i]) && line[i] != ' ')
			print_error("ERROR - There is wrong word in resolution info");
		i++;
	}
	i = 0;
	while (lines[i])
		i++;
	if (i != 2)
		print_error("ERROR - There are too many or small resolution info");
	map->resolution[0] = ft_atoi(lines[0]);
	map->resolution[1] = ft_atoi(lines[1]);
	free_all(lines);
}

void		make_texture(t_game *game, int i)
{
	int		y;
	int		x;
	t_stick	*s;

	s = &game->stick;
	if (!(s->img = mlx_xpm_file_to_image(game->vars.mlx, game->map.textures[i]
		, &s->width, &s->height)))
		print_error("ERROR - file is wrong");
	s->addr = (int*)mlx_get_data_addr(s->img, &s->bits_per_pixel
		, &s->line_length, &s->endian);
	if (!(game->tex.tex[i] = malloc(sizeof(int) * s->width * s->height)))
		print_error("ERROR - memory allcated failed");
	game->tex.tex_height[i] = s->height;
	game->tex.tex_width[i] = s->width;
	if (s->img == 0)
		print_error("ERROR - Wrong xpm file");
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
