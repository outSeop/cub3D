#include "cub3D.h"

int worldMap[mapWidth][mapHeight]=
{
 {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,7,7,7,7,7,7,7},
  {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
  {4,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
  {4,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
  {4,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
  {4,0,4,0,0,0,0,5,5,5,5,5,5,5,5,5,7,7,0,7,7,7,7,7},
  {4,0,5,0,0,0,0,5,0,5,0,5,0,5,0,5,7,0,0,0,7,7,7,1},
  {4,0,6,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
  {4,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,1},
  {4,0,8,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
  {4,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,7,7,7,1},
  {4,0,0,0,0,0,0,5,5,5,5,0,5,5,5,5,7,7,7,7,7,7,7,1},
  {6,6,6,6,6,6,6,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
  {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
  {6,6,6,6,6,6,0,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
  {4,4,4,4,4,4,0,4,4,4,6,0,6,2,2,2,2,2,2,2,3,3,3,3},
  {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
  {4,0,0,0,0,0,0,0,0,0,0,0,6,2,0,0,5,0,0,2,0,0,0,2},
  {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
  {4,0,6,0,6,0,0,0,0,4,6,0,0,0,0,0,5,0,0,0,0,0,0,2},
  {4,0,0,5,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
  {4,0,6,0,6,0,0,0,0,4,6,0,6,2,0,0,5,0,0,2,0,0,0,2},
  {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
  {4,4,4,4,4,4,4,4,4,4,1,1,1,2,2,2,2,2,2,3,3,3,3,3}

};

void		engine(t_game *game)
{
	int		pixel_x;
	int		hit;

	pixel_x = 0;
		mlx_clear_window(game->vars.mlx, game->vars.win);
	while (pixel_x < WIDTH)
	{
		game->ray.camera_x = 2 * pixel_x / (double)WIDTH - 1;
		game->ray.dir_x = game->player.dir_x + game->ray.camera_x * game->ray.plane_x;
		game->ray.dir_y = game->player.dir_y + game->ray.camera_x * game->ray.plane_y;
		game->ray.map_x = (int)game->player.pos_x;
		game->ray.map_y = (int)game->player.pos_y;
		game->ray.delta_dist_x = fabs(1 / game->ray.dir_x);
		game->ray.delta_dist_y = fabs(1 / game->ray.dir_y);


		if (game->ray.dir_x < 0)
		{
			game->ray.step_x = -1;
			game->ray.side_dist_x = (game->player.pos_x - game->ray.map_x) * game->ray.delta_dist_x;
		}
		else
		{
			game->ray.step_x = 1;
			game->ray.side_dist_x = (game->ray.map_x + 1.0 - game->player.pos_x) * game->ray.delta_dist_x;
		}
		if (game->ray.dir_y < 0)
		{
			game->ray.step_y = -1;
			game->ray.side_dist_y = (game->player.pos_y - game->ray.map_y) * game->ray.delta_dist_y;
		}
		else
		{
			game->ray.step_y = 1;
			game->ray.side_dist_y = (game->ray.map_y + 1.0 - game->player.pos_y) * game->ray.delta_dist_y;
		}
		hit = 0;
		while (hit == 0)
		{
			if (game->ray.side_dist_x < game->ray.side_dist_y)
			{
				game->ray.side_dist_x += game->ray.delta_dist_x;
				game->ray.map_x += game->ray.step_x;
				game->ray.side = 0;
			}
			else
			{
				game->ray.side_dist_y += game->ray.delta_dist_y;
				game->ray.map_y += game->ray.step_y;
				game->ray.side = 1;
			}
			if (worldMap[game->ray.map_x][game->ray.map_y] > 0)
				hit = 1;
		}
		if (game->ray.side == 0)
			game->ray.prep_wall_dist = (game->ray.map_x - game->player.pos_x + (1 - game->ray.step_x) / 2) / game->ray.dir_x;
		else
			game->ray.prep_wall_dist = (game->ray.map_y - game->player.pos_y + (1 - game->ray.step_y) / 2) / game->ray.dir_y;
		game->draw.line_height = (int)(HEIGHT / game->ray.prep_wall_dist * 1.2);
		game->draw.draw_start = -(game->draw.line_height) / 2 + HEIGHT;
		if (game->draw.draw_start < 0)
			game->draw.draw_start = 0;
		game->draw.draw_end = game->draw.line_height / 2 + HEIGHT;
		if (game->draw.draw_end >= HEIGHT * 2)
			game->draw.draw_end = HEIGHT * 2 - 1;

		game->tex.num = worldMap[game->ray.map_x][game->ray.map_y] - 1;
		if (game->ray.side == 0)
			game->tex.wall_x = game->player.pos_y + game->ray.prep_wall_dist * game->ray.dir_y;
		else
			game->tex.wall_x = game->player.pos_x + game->ray.prep_wall_dist * game->ray.dir_x;
		game->tex.wall_x -= floor(game->tex.wall_x);

		game->tex.tex_x = (int)(game->tex.wall_x * (double)TEX_WIDTH);
		if (game->ray.side == 0 && game->ray.dir_x > 0)
			game->tex.tex_x = TEX_WIDTH - game->tex.tex_x - 1;
		if (game->ray.side == 1 && game->ray.dir_y < 0)
			game->tex.tex_x = TEX_WIDTH - game->tex.tex_x - 1;
		game->tex.step = 1.0 * TEX_HEIGHT / game->draw.line_height;
		game->tex.tex_pos = (game->draw.draw_start - HEIGHT+ game->draw.line_height / 2) * game->tex.step;
		for (int i = game->draw.draw_start; i < game->draw.draw_end; i++)
		{
			game->tex.tex_y = (int)game->tex.tex_pos & (TEX_HEIGHT - 1);
			game->tex.tex_pos += game->tex.step;
			int color = g_texture[game->tex.num][TEX_HEIGHT * game->tex.tex_y + game->tex.tex_x];
			if (game->ray.side == 1)
				color = (color >> 1) & 0x007f7f7f;
			my_mlx_pixel_put(&game->stick, pixel_x, i, color);
		}
		pixel_x++;
	}
		mlx_put_image_to_window(game->vars.mlx, game->vars.win, game->stick.img, 0, -(HEIGHT / 2) + game->player.jump);

		init_stick(game);
}
void		start(t_game *game)
{
	mlx_hook(game->vars.win, 2, 0, key_press, &(game->vars));
	mlx_hook(game->vars.win, 3, 0, key_release, &(game->vars));
	mlx_hook(game->vars.win, 6, 0, catch_mouse_move, &(game->vars));
	mlx_loop_hook(game->vars.mlx, main_loop, game);
	mlx_loop(game->vars.mlx);
}
