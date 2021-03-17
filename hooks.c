#include "cub3D.h"

int				catch_mouse_move()
{
	g_check = 1;
}

void			get_mouse_pos(t_game *game)
{
	mlx_mouse_get_pos(game->vars.win, &(game->mouse.pos_x), &(game->mouse.pos_y));
	g_check = 0;
}

void			hide_mouse_pointer(t_game *game)
{
	if (game->mouse.playing == 1)
		mlx_mouse_hide();
	else
		mlx_mouse_show();
}

void			hold_in_senter(t_game *game)
{
	if (game->mouse.playing == 1)
	{
		if (game->mouse.pos_x < game->ray.width / 2)
		{
			game->turn_left = 0;
			game->turn_right = 1;
		}
		else if (game->mouse.pos_x > game->ray.width / 2)
		{
			game->turn_right = 0;
			game->turn_left = 1;
		}
		else
		{
			game->turn_left = 0;
			game->turn_right = 0;
		}
		mlx_mouse_move(game->vars.win, game->ray.width / 2, game->ray.height / 2);
	}
}
