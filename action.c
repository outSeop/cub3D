/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inssong <inssong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 05:02:17 by inssong           #+#    #+#             */
/*   Updated: 2021/05/27 08:17:02 by inssong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		if (check_out((int)g->player.pos_y, (int)g->player.pos_x, g))
		{
			g->player.pos_x = temp_pox_x;
			g->player.pos_y = temp_pox_y;
		}
	}
	if (g->moving_behind)
	{
		g->player.pos_x -= g->player.dir_x * MOVESPEED;
		g->player.pos_y -= g->player.dir_y * MOVESPEED;
		if (check_out((int)g->player.pos_y, (int)g->player.pos_x, g))
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
	if (g->moving_left)
	{
		g->player.pos_y += g->player.dir_x * MOVESPEED;
		g->player.pos_x -= g->player.dir_y * MOVESPEED;
		if (check_out((int)g->player.pos_y, (int)g->player.pos_x, g))
		{
			g->player.pos_x = temp_pox_x;
			g->player.pos_y = temp_pox_y;
		}
	}
	if (g->moving_right)
	{
		g->player.pos_y -= g->player.dir_x * MOVESPEED;
		g->player.pos_x += g->player.dir_y * MOVESPEED;
		if (check_out((int)g->player.pos_y, (int)g->player.pos_x, g))
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

int				check_out(int y, int x, t_game *g)
{
	if (y < 0 || y > g->map.height || x < 0
		|| x >= (int)ft_strlen(g->map.map[y])
		|| g->map.map[y][x] == ' ')
		return (1);
	if (g->map.map[y][x] == '1')
		return (1);
	return (0);
}
