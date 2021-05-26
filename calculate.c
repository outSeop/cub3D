#include "cub3D.h"

void		calc_forward_aixs(t_ray *ray)
{
	if (ray->side_dist_x < ray->side_dist_y)
	{
		ray->side_dist_x += ray->delta_dist_x;
		ray->map_x += ray->step_x;
		ray->side = 0;
		ray->direction = WE;
		if (ray->step_x == -1)
			ray->direction = EA;
	}
	else
	{
		ray->side_dist_y += ray->delta_dist_y;
		ray->map_y += ray->step_y;
		ray->side = 1;
		ray->direction = SO;
		if (ray->step_y == -1)
			ray->direction = NO;
	}
}

void		calc_perp_dist(t_ray *ray, t_player *player)
{
	if (ray->side == 0)
	{
		ray->perp_dist = (ray->map_x - player->pos_x + (1 - ray->step_x) / 2);
		ray->perp_dist /= ray->dir_x;
	}
	else
	{
		ray->perp_dist = (ray->map_y - player->pos_y + (1 - ray->step_y) / 2);
		ray->perp_dist /= ray->dir_y;
	}
}
