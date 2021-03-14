#include "cub3D.h"

void	set_draw_info(t_draw *draw, t_ray *ray)
{
		draw->line_height = (int)(HEIGHT / ray->perp_dist * 1.2);
		draw->draw_start = -(draw->line_height) / 2 + HEIGHT / 2;
		if (draw->draw_start < 0)
			draw->draw_start = 0;
		draw->draw_end = draw->line_height / 2 + HEIGHT / 2;
		if (draw->draw_end >= HEIGHT)
			draw->draw_end = HEIGHT - 1;
}

void	set_tex_info(t_game *game)
{
	game->tex.num = game->map.map[game->ray.map_x][game->ray.map_y] - 48 - 1;
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
	game->tex.tex_pos = (game->draw.draw_start - HEIGHT / 2 + game->draw.line_height / 2);
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
	while (i < HEIGHT)
		my_mlx_pixel_put(&game->stick, pixel_x, i++, game->map.floor);
}
