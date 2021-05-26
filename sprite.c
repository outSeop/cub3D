/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inssong <inssong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 05:04:34 by inssong           #+#    #+#             */
/*   Updated: 2021/05/27 07:04:15 by inssong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			buffering_sprite(t_game *game)
{
	t_sprite	*head;

	head = game->sprite;
	game->sprite = game->sprite->next;
	while (game->sprite)
	{
		calc_sprite_xy(game);
		calc_draw_start_end(game);
		buffering_sprite_pixel(game, &game->spinfo, &game->tex);
		game->sprite = game->sprite->next;
	}
	game->sprite = head;
}

void			calc_sprite_xy(t_game *game)
{
	game->spinfo.sprite_x = game->sprite->sprite_x - game->player.pos_x;
	game->spinfo.sprite_y = game->sprite->sprite_y - game->player.pos_y;
	game->spinfo.inv_det = 1.0 / (game->ray.plane_x * game->player.dir_y
		- game->ray.plane_y * game->player.dir_x);
	game->spinfo.transform_x =
		game->spinfo.inv_det * (game->player.dir_y * game->spinfo.sprite_x
		- game->player.dir_x * game->spinfo.sprite_y);
	game->spinfo.transform_y = game->spinfo.inv_det * (-game->ray.plane_y
		* game->spinfo.sprite_x + game->ray.plane_x * game->spinfo.sprite_y);
	game->spinfo.sprtie_screen_x = (int)((game->ray.width / 2)
		* (1 + game->spinfo.transform_x / game->spinfo.transform_y));
	game->spinfo.sprite_height =
		abs((int)(game->ray.height / (game->spinfo.transform_y)));
}

void			calc_draw_start_end(t_game *game)
{
	int			draw_start_y;
	int			draw_end_y;
	int			draw_start_x;
	int			draw_end_x;

	draw_start_y = -game->spinfo.sprite_height / 2 + game->ray.height / 2;
	if (draw_start_y < 0)
		draw_start_y = 0;
	draw_end_y = game->spinfo.sprite_height / 2 + game->ray.height / 2;
	if (draw_end_y > game->ray.height)
		draw_end_y = game->ray.height - 1;
	game->spinfo.sprite_width =
		abs((int)(game->ray.height / game->spinfo.transform_y));
	draw_start_x = -game->spinfo.sprite_width
		/ 2 + game->spinfo.sprtie_screen_x;
	if (draw_start_x < 0)
		draw_start_x = 0;
	draw_end_x = game->spinfo.sprite_width
		/ 2 + game->spinfo.sprtie_screen_x;
	if (draw_end_x >= game->ray.width)
		draw_end_x = game->ray.width - 1;
	game->spinfo.draw_start_y = draw_start_y;
	game->spinfo.draw_end_y = draw_end_y;
	game->spinfo.draw_start_x = draw_start_x;
	game->spinfo.draw_end_x = draw_end_x;
}

void			buffering_sprite_pixel(t_game *game, t_spinfo *s, t_texture *t)
{
	int			i;
	int			j;
	int			color;
	int			d;

	i = s->draw_start_x - 1;
	while (++i < s->draw_end_x)
	{
		s->tex_x = (int)(256 * (i - (-s->sprite_width / 2 + s->sprtie_screen_x))
			* t->tex_width[S] / s->sprite_width) / 256;
		if (s->transform_y > 0 && i > 0 && i < game->ray.width
			&& s->transform_y < game->z_buffer[i])
		{
			j = s->draw_start_y - 1;
			while (++j < s->draw_end_y)
			{
				d = j * 256 - game->ray.height * 128 + s->sprite_height * 128;
				s->tex_y = ((d * t->tex_height[S] / s->sprite_height) / 256);
				color = t->tex[S][t->tex_width[S] * s->tex_y + s->tex_x];
				if (color == (int)0xff000000)
					continue;
				my_mlx_pixel_put(&game->stick, i, j, color);
			}
		}
	}
}
