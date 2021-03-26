#include "cub3D.h"

void		engine(t_game *game)
{
	int		pixel_x;
	int		hit;

	pixel_x = 0;
	mlx_clear_window(game->vars.mlx, game->vars.win);
	game->z_buffer = malloc(sizeof(double) * (game->ray.width + 1));
	game->sprite = malloc(sizeof(t_sprite));
	game->sprite->next = NULL;
	game->ray.num_sprite = 0;
	while (pixel_x < game->ray.width)
	{
		game->ray.camera_x = 2 * pixel_x / (double)game->ray.width - 1;
		set_ray_info(&game->ray, &game->player);
		check_hit(&game->ray, &game->map, game->sprite);
		calc_perp_dist(&game->ray, &game->player);
		set_draw_info(&game->draw, &game->ray);
		set_tex_info(game);
		buffering_pixels(game, pixel_x);
		pixel_x++;
		game->z_buffer[pixel_x] = game->ray.perp_dist;
	}
	calc_sprite_distance(game->sprite, &game->player);
	mlx_put_image_to_window(game->vars.mlx, game->vars.win, game->stick.img, 0, 0);
	free(game->z_buffer);
	free(game->sprite);
	ft_memset(game->map.map_s, 0, game->ray.map_size);
	init_stick(game);
}

void			set_ray_info(t_ray *ray, t_player *player)
{
		ray->dir_x = player->dir_x + ray->camera_x * ray->plane_x;
		ray->dir_y = player->dir_y + ray->camera_x * ray->plane_y;
		ray->map_x = (int)player->pos_x;
		ray->map_y = (int)player->pos_y;
		ray->delta_dist_x = fabs(1 / ray->dir_x);
		ray->delta_dist_y = fabs(1 / ray->dir_y);
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - player->pos_x) * ray->delta_dist_x;
		if (ray->dir_x < 0)
		{
			ray->step_x = -1;
			ray->side_dist_x = (player->pos_x - ray->map_x) * ray->delta_dist_x;
		}
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - player->pos_y) * ray->delta_dist_y;
		if (ray->dir_y < 0)
		{
			ray->step_y = -1;
			ray->side_dist_y = (player->pos_y - ray->map_y) * ray->delta_dist_y;
		}
}

void			check_hit(t_ray *ray, t_map *map, t_sprite *sprite)
{
	while (1)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
			ray->direction = SO;
			if (ray->step_x == -1)
				ray->direction = NO;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
			ray->direction = WE;
			if (ray->step_y == -1)
				ray->direction = EA;
		}
		if (map->map[ray->map_x][ray->map_y] == '2' && !map->map_s[ray->map_x][ray->map_y])
		{
			add_sprite(sprite, ray);
			ray->num_sprite++;
			map->map_s[ray->map_x][ray->map_y] = 1;
		}
		if (map->map[ray->map_x][ray->map_y] == '1')
			return ;
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


void		start(t_game *game)
{
	mlx_hook(game->vars.win, 2, 0, key_press, &(game->vars));
	mlx_hook(game->vars.win, 3, 0, key_release, &(game->vars));
	//mlx_hook(game->vars.win, 6, 0, catch_mouse_move, &(game->vars));
	mlx_loop_hook(game->vars.mlx, main_loop, game);
	mlx_loop(game->vars.mlx);
}
