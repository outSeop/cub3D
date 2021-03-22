#include "cub3D.h"

void		engine(t_game *game)
{
	int		pixel_x;
	int		hit;

	game->sprite = malloc(sizeof(t_sprite));
	game->sprite->next = 0;
	pixel_x = 0;
	mlx_clear_window(game->vars.mlx, game->vars.win);
	while (pixel_x < game->ray.width)
	{
		game->ray.camera_x = 2 * pixel_x / (double)game->ray.width - 1;
		set_ray_info(&game->ray, &game->player);
		check_hit(&game->ray, &game->map, &game->player, game->sprite);
		calc_perp_dist(&game->ray, &game->player);
		set_draw_info(&game->draw, &game->ray);
		set_tex_info(game);
		buffering_pixels(game, pixel_x);

		// sprite
		game->z_buffer[pixel_x] = game->ray.perp_dist;

		pixel_x++;
	}
	sort_sprite(game->sprite);

	while (game->sprite)
	{
		double	sprite_x = game->sprite->x - game->player.pos_x;
		double	sprite_y = game->sprite->y - game->player.pos_y;

		double	inv_det = 1.0 / (game->ray.plane_x * game->player.dir_y - game->ray.plane_y * game->ray.plane_x);

		double trans_x = inv_det * (game->player.dir_x * sprite_x - game->player.dir_y * sprite_y);
		double trans_y = inv_det * (-game->ray.plane_y * sprite_x + game->ray.plane_x * sprite_y);

		int	sprite_screen_x = (int)(game->ray.width / 2) * (1 + trans_x / trans_y);

		int	sprite_height = (int)fabs((game->ray.height / trans_y));
		int	draw_start_y = -sprite_height / 2 + game->ray.height / 2;
		if (draw_start_y < 0)
			draw_start_y = 0;
		int draw_end_y = sprite_height / 2 + game->ray.height / 2;
		if (draw_end_y >= game->ray.height)
			draw_end_y = game->ray.height;

		int	sprite_width = (int)fabs((game->ray.height / trans_y));
		int	draw_start_x = -sprite_width / 2 + sprite_screen_x;
		if (draw_start_x < 0)
			draw_start_x = 0;
		int draw_end_x = sprite_width / 2 + sprite_screen_x;
		if (draw_end_x >= game->ray.width)
			draw_end_x = game->ray.width - 1;

		for (int i = draw_start_x; i < draw_end_x; i++)
		{
			int tex_x= (int)((256 * (i - (-sprite_width / 2 + sprite_screen_x)) * game->stick.width / sprite_width) / 256);
			if (trans_y > 0 && i > 0 && i < game->ray.width && trans_y < game->z_buffer[i])
			{
				for (int j = draw_start_y; j < draw_end_y; j++)
				{
					int d = j * 256 - game->ray.height * 128 + sprite_height * 128;
					int tex_y = ((d * game->stick.height) / sprite_height) / 256;
					int color = g_texture[4][game->stick.width * tex_y + tex_x];
					if ((color & 0x00FFFFFF) != 0)
						my_mlx_pixel_put(&game->stick, j, i, color);
				}
			}
		}
		game->sprite = game->sprite->next;
	}
	free(game->sprite);
	draw(game);
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

void			check_hit(t_ray *ray, t_map *map, t_player *player, t_sprite *sprite)
{
	while (1)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->tex = EA;
			if (ray->step_x == -1)
				ray->tex = WE;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->tex = SO;
			if (ray->step_y == -1)
				ray->tex = NO;
			ray->side = 1;
		}
		if (map->map[ray->map_x][ray->map_y] == '1')
			return ;
		else if (map->map[ray->map_x][ray->map_y] == '2')
			add_sprite(sprite, player, ray->map_x, ray->map_y);
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
