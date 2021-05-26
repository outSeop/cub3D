#include "cub3D.h"

void			move_fb(t_game *g)
{
	double		temp_pox_x;
	double		temp_pox_y;

	temp_pox_x = g->player.pos_x;
	temp_pox_y = g->player.pos_y;
	if (g->moving_forward)
	{
		g->player.pos_x += g->player.dir_x * MOVESPEED;
		g->player.pos_y += g->player.dir_y * MOVESPEED;
		if (g->map.map[(int)g->player.pos_y][(int)g->player.pos_x] == '1')
		{
			g->player.pos_x = temp_pox_x;
			g->player.pos_y = temp_pox_y;
		}
	}
	if (g->moving_behind)
	{
		g->player.pos_x -= g->player.dir_x * MOVESPEED;
		g->player.pos_y -= g->player.dir_y * MOVESPEED;
		if (g->map.map[(int)g->player.pos_y][(int)g->player.pos_x] == '1')
		{
			g->player.pos_x = temp_pox_x;
			g->player.pos_y = temp_pox_y;
		}
	}
}

void			move_rl(t_game *g)
{
	double		temp_pox_x;
	double		temp_pox_y;

	temp_pox_x = g->player.pos_x;
	temp_pox_y = g->player.pos_y;
	if (g->moving_right)
	{
		g->player.pos_y += g->player.dir_x * MOVESPEED;
		g->player.pos_x -= g->player.dir_y * MOVESPEED;
		if (g->map.map[(int)g->player.pos_y][(int)g->player.pos_x] == '1')
		{
			g->player.pos_x = temp_pox_x;
			g->player.pos_y = temp_pox_y;
		}
	}
	if (g->moving_left)
	{
		g->player.pos_y -= g->player.dir_x * MOVESPEED;
		g->player.pos_x += g->player.dir_y * MOVESPEED;
		if (g->map.map[(int)g->player.pos_y][(int)g->player.pos_x] == '1')
		{
			g->player.pos_x = temp_pox_x;
			g->player.pos_y = temp_pox_y;
		}
	}
}

void			turn_rl(t_game *g)
{
	double		old_dir_x;
	double		old_plane_x;
	t_player	*p;
	t_ray		*r;

	p = &g->player;
	r = &g->ray;
	if (g->turn_left)
	{
		old_dir_x = p->dir_x;
		p->dir_x = p->dir_x * cos(T_SPEED) - p->dir_y * sin(T_SPEED);
		p->dir_y = old_dir_x * sin(T_SPEED) + p->dir_y * cos(T_SPEED);
		old_plane_x = r->plane_x;
		r->plane_x = r->plane_x * cos(T_SPEED) - r->plane_y * sin(T_SPEED);
		r->plane_y = old_plane_x * sin(T_SPEED) + r->plane_y * cos(T_SPEED);
	}
	if (g->turn_right)
	{
		old_dir_x = p->dir_x;
		p->dir_x = p->dir_x * cos(-T_SPEED) - p->dir_y * sin(-T_SPEED);
		p->dir_y = old_dir_x * sin(-T_SPEED) + p->dir_y * cos(-T_SPEED);
		old_plane_x = r->plane_x;
		r->plane_x = r->plane_x * cos(-T_SPEED) - r->plane_y * sin(-T_SPEED);
		r->plane_y = old_plane_x * sin(-T_SPEED) + r->plane_y * cos(-T_SPEED);
	}
}
