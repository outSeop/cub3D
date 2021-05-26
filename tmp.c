/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inssong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 05:04:44 by inssong           #+#    #+#             */
/*   Updated: 2021/05/27 05:04:44 by inssong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
		game->tex.wall_x =
			game->player.pos_y + game->ray.perp_dist * game->ray.dir_y;
	else
		game->tex.wall_x =
			game->player.pos_x + game->ray.perp_dist * game->ray.dir_x;
	game->tex.wall_x -= floor(game->tex.wall_x);
	game->tex.tex_x =
		(int)(game->tex.wall_x * (double)game->tex.tex_width[game->tex.num]);
	if (game->ray.side == 0 && game->ray.dir_x > 0)
		game->tex.tex_x =
			game->tex.tex_width[game->tex.num] - game->tex.tex_x - 1;
	if (game->ray.side == 1 && game->ray.dir_y < 0)
		game->tex.tex_x =
			game->tex.tex_width[game->tex.num] - game->tex.tex_x - 1;
	game->tex.step =
		1.0 * game->tex.tex_height[game->tex.num] / game->draw.line_height;
	game->tex.tex_pos =
	(game->draw.draw_start - game->ray.height / 2 + game->draw.line_height / 2);
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
		game->tex.tex_y =
			(int)game->tex.tex_pos & (game->tex.tex_height[game->tex.num] - 1);
		game->tex.tex_pos += game->tex.step;
		color = game->tex.tex[game->tex.num][game->tex.tex_height[game->tex.num]
			* game->tex.tex_y + game->tex.tex_x];
		if (game->ray.side == 1)
			color = (color >> 1) & 0x007f7f7f;
		my_mlx_pixel_put(&game->stick, pixel_x, i, color);
		i++;
	}
	while (i < game->ray.height)
		my_mlx_pixel_put(&game->stick, pixel_x, i++, game->map.floor);
}
