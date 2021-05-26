#include "cub3D.h"

int				main_loop(t_game *game)
{
	move_fb(game);
	move_rl(game);
	turn_rl(game);
	engine(game);
	return (0);
}

int				key_press(int keycode, t_game *game)
{
	if (keycode == ESC)
	{
		close_window(&(game->vars));
		exit(0);
	}
	if (keycode == KEY_W)
		game->moving_forward = 1;
	if (keycode == KEY_S)
		game->moving_behind = 1;
	if (keycode == KEY_LEFT)
		game->turn_left = 1;
	if (keycode == KEY_RIGHT)
		game->turn_right = 1;
	if (keycode == KEY_D)
		game->moving_right = 1;
	if (keycode == KEY_A)
		game->moving_left = 1;
	return (0);
}

int				key_release(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->moving_forward = 0;
	if (keycode == KEY_S)
		game->moving_behind = 0;
	if (keycode == KEY_LEFT)
		game->turn_left = 0;
	if (keycode == KEY_RIGHT)
		game->turn_right = 0;
	if (keycode == KEY_D)
		game->moving_right = 0;
	if (keycode == KEY_A)
		game->moving_left = 0;
	return (0);
}

int				close_window(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	return (0);
}

void			my_mlx_pixel_put(t_stick *data, int x, int y, int color)
{
	char	*dst;

	dst = (char*)data->addr + (y * data->line_length
		+ x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
