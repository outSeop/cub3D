/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inssong <inssong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 05:03:58 by inssong           #+#    #+#             */
/*   Updated: 2021/05/27 07:04:13 by inssong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			init_game(t_game *game)
{
	game->angle = 0;
	game->moving_forward = 0;
	game->moving_behind = 0;
	game->moving_left = 0;
	game->moving_right = 0;
	game->turn_left = 0;
	game->turn_right = 0;
	init_vars(game);
	init_ray(game);
	init_stick(game);
	game->tex.tex = (void*)malloc(sizeof(void*) * 5);
	game->player.check = 0;
}

void			init_ray(t_game *game)
{
	game->ray.camera_x = 0;
	game->ray.map_x = 0;
	game->ray.map_y = 0;
	game->ray.side_dist_x = 0;
	game->ray.side_dist_y = 0;
	game->ray.delta_dist_x = 0;
	game->ray.delta_dist_y = 0;
	game->ray.perp_dist = 0;
	game->ray.step_x = 0;
	game->ray.step_y = 0;
	game->ray.side = 0;
	game->ray.num_sprite = 0;
	game->ray.map_size = 0;
	game->ray.plane_x = game->player.dir_y * 0.66;
	game->ray.plane_y = -game->player.dir_x * 0.66;
}

void			init_stick(t_game *game)
{
	game->stick.img =
		mlx_new_image(game->vars.mlx, game->ray.width, game->ray.height);
	game->stick.addr =
		(int*)mlx_get_data_addr(game->stick.img, &game->stick.bits_per_pixel
		, &game->stick.line_length, &game->stick.endian);
}

void			init_vars(t_game *game)
{
	game->vars.mlx = mlx_init();
	game->vars.win =
	mlx_new_window(game->vars.mlx, game->ray.width, game->ray.height, "title");
}

void			init_map(t_game *game)
{
	game->map.map = NULL;
	game->map.textures[0] = NULL;
	game->map.textures[1] = NULL;
	game->map.textures[2] = NULL;
	game->map.textures[3] = NULL;
	game->map.textures[4] = NULL;
	game->map.chk_dp[0] = 0;
	game->map.chk_dp[1] = 0;
	game->map.chk_dp[2] = 0;
	game->map.chk_dp[3] = 0;
	game->map.chk_dp[4] = 0;
	game->map.chk_dp[5] = 0;
	game->map.chk_dp[6] = 0;
	game->map.chk_dp[7] = 0;
	game->map.floor = 0;
	game->map.celling = 0;
}
