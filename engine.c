#include "cub3D.h"

void		engine(t_game *game)
{
	int		pixel_x;
	int		hit;
	char	**temp;

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
	//sort_sprite(game->sprite);
	int i = 0;
	t_sprite *s = game->sprite;
	while (s)
	{
		printf("%d ", i++);
		printf("==%lf==\n", s->distance);
		s = s->next;
	}
	buffering_sprite(game);

	mlx_put_image_to_window(game->vars.mlx, game->vars.win, game->stick.img, 0, 0);
	free(game->z_buffer);
	//free_sprite(game->sprite);
	// ft_memset(game->map.map_s, 0, game->ray.map_size);
	init_stick(game);
	int ii = 0;
	while (ii < game->map.height)
	{
		int j = 0;
		while (game->map.map[ii][j])
		{
			if (game->map.map[ii][j] == '3')
				game->map.map[ii][j] = '2';
			j++;
		}
		ii++;
	}
}
void			buffering_sprite(t_game *game)
{
	int			i;
	int			color;
	double		sprite_x;
	double		sprite_y;

	while (game->sprite)
	{
		sprite_x = game->sprite->sprite_x - game->player.pos_x;
		sprite_y = game->sprite->sprite_y - game->player.pos_y;

		double invDet = 1.0 / (game->ray.plane_x * game->ray.dir_y - game->ray.plane_y * game->ray.dir_x);
		double transform_x = invDet * (game->ray.dir_y * sprite_x - game->ray.dir_x * sprite_y);
		double transform_y = invDet * (- game->ray.plane_y * sprite_x + game->ray.plane_x * sprite_y);

		int  sprtie_screen_x = (int)((game->ray.width / 2) * (1 + transform_x / transform_y));

		int sprite_height = abs((int)(game->ray.height / (transform_y)));
		int draw_start_y = - sprite_height / 2 + game->ray.height / 2;
		if (draw_start_y < 0)
			draw_start_y = 0;
		int draw_end_y = sprite_height / 2 + game->ray.height / 2;
		if (draw_end_y > game->ray.height)
			draw_end_y = game->ray.height - 1;

		int sprite_width = abs((int)(game->ray.height / transform_y));
		int draw_start_x = -sprite_width / 2 + sprtie_screen_x;
		if (draw_start_x < 0)
			draw_start_x = 0;
		int draw_end_x = sprite_width / 2  + sprtie_screen_x;
		if (draw_end_x >= sprtie_screen_x)
			draw_end_x = sprtie_screen_x - 1;

		i = 0;
		for (i = draw_start_x; i < draw_end_x; i++)
		{
			int tex_x = (int)(256 * (i - (-sprite_width / 2 + sprtie_screen_x)) * TEX_WIDTH / sprite_width) / 256;
			if (transform_y > 0 && i > 0 && i < game->ray.width && transform_y < game->z_buffer[i])
			{
				int j = 0;
				for (j = draw_start_y; j < draw_end_y; j++)
				{
					int d = j * 256 - game->ray.height * 128 + sprite_height * 128;
					int tex_y = ((d * TEX_HEIGHT) / sprite_height) / 256;
					color = game->tex.tex[S][TEX_WIDTH * tex_y + tex_x];
					my_mlx_pixel_put(&game->stick, i, j, color);
				}
			}
		}
		game->sprite = game->sprite->next;

	}
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
		if (map->map[ray->map_x][ray->map_y] == '2')
		{
			add_sprite(sprite, ray);
			ray->num_sprite++;
			map->map[ray->map_x][ray->map_y] = '3';
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
