#include "cub3D.h"
/*
int				main(void)
{
	t_game		game;


	make_texture();
	init_game(&game);
	engine(&game);
	start(&game);
}
*/
int				main_loop(t_game *game)
{
	double		temp_pox_x;
	double		temp_pox_y;

	temp_pox_x = game->player.pos_x;
	temp_pox_y = game->player.pos_y;
	if (game->moving_forward)
	{
		game->player.pos_x += game->player.dir_x * MOVESPEED;
		game->player.pos_y += game->player.dir_y * MOVESPEED;
		if (game->map.map[(int)game->player.pos_y][(int)game->player.pos_x] == '1')
		{
			game->player.pos_x = temp_pox_x;
			game->player.pos_y = temp_pox_y;
		}
	}
	else if (game->moving_behind)
	{
		game->player.pos_x -= game->player.dir_x * MOVESPEED;
		game->player.pos_y -= game->player.dir_y * MOVESPEED;
		if (game->map.map[(int)game->player.pos_y][(int)game->player.pos_x] == '1')
		{
			game->player.pos_x = temp_pox_x;
			game->player.pos_y = temp_pox_y;
		}
	}
	if (game->turn_right)
	{
		double old_dir_x = game->player.dir_x;
		game->player.dir_x = game->player.dir_x * cos(TURNSPEED) - game->player.dir_y * sin(TURNSPEED);
		game->player.dir_y = old_dir_x * sin(TURNSPEED) + game->player.dir_y * cos(TURNSPEED);
		double old_plane_x = game->ray.plane_x;
		game->ray.plane_x = game->ray.plane_x * cos(TURNSPEED) - game->ray.plane_y * sin(TURNSPEED);
		game->ray.plane_y = old_plane_x * sin(TURNSPEED) + game->ray.plane_y * cos(TURNSPEED);
	}
	else if (game->turn_left)
	{
		double old_dir_x = game->player.dir_x;
		game->player.dir_x = game->player.dir_x * cos(-TURNSPEED) - game->player.dir_y * sin(-TURNSPEED);
		game->player.dir_y = old_dir_x * sin(-TURNSPEED) + game->player.dir_y * cos(-TURNSPEED);
		double old_plane_x = game->ray.plane_x;
		game->ray.plane_x = game->ray.plane_x * cos(-TURNSPEED) - game->ray.plane_y * sin(-TURNSPEED);
		game->ray.plane_y = old_plane_x * sin(-TURNSPEED) + game->ray.plane_y * cos(-TURNSPEED);
	}
	/*
	if (game->mouse.playing == 1)
	{
		mlx_mouse_get_pos(game->vars.win, &(game->mouse.pos_x), &(game->mouse.pos_y));
		hold_in_senter(game);
	}
	hide_mouse_pointer(game);
	*/
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
	else if (keycode == KEY_W)
		game->moving_forward = 1;
	else if (keycode == KEY_S)
		game->moving_behind = 1;
	else if (keycode == KEY_D)
		game->turn_right = 1;
	else if (keycode == KEY_A)
		game->turn_left = 1;
	if (keycode == 50)
		game->mouse.playing = 1 - game->mouse.playing;
		return (0);
}

int				key_release(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->moving_forward = 0;
	else if (keycode == KEY_S)
		game->moving_behind = 0;
	else if (keycode == KEY_D)
		game->turn_right = 0;
	else if (keycode == KEY_A)
		game->turn_left = 0;
		return (0);
}

int				close_window(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	return (0);
}

void            my_mlx_pixel_put(t_stick *data, int x, int y, int color)
{
    char   *dst;

    dst = (char*)data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}
