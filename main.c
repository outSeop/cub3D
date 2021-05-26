/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inssong <inssong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 05:04:05 by inssong           #+#    #+#             */
/*   Updated: 2021/05/27 08:27:17 by inssong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			main(int argc, char *argv[])
{
	t_game	game;

	prepare(&game, argc, argv);
	limit(&game);
	init_game(&game);
	load_textures(&game);
	if (game.sc == 1)
	{
		bitmap(&game);
		save_bitmap(&game);
		return (0);
	}
	start(&game);
	return (0);
}

void		prepare(t_game *game, int argc, char *argv[])
{
	int		fd;

	game->map.height = 0;
	if ((fd = error_input(argc, argv, &game->sc)) == -1)
		print_error("ERROR - There is no file");
	init_map(game);
	game->player.check = 0;
	if (parsing_cub(&game->map, fd) == -1)
		print_error("13");
	if (!(parsing_map(fd, &game->player, &game->map.height, &game->map)))
		print_error("23");
	if (!check_map(game->map.map_visited
		, (int)game->player.pos_x, (int)game->player.pos_y, game->map.height))
		print_error("ERROR - The map is invalid");
	error_file(&game->map);
	game->ray.width = game->map.resolution[0];
	game->ray.height = game->map.resolution[1];
	if (game->player.check != 1)
		print_error("ERROR - Too many players or invalid word");
}

void		limit(t_game *game)
{
	int x;
	int	y;

	mlx_get_screen_size(game->vars.mlx, &x, &y);
	if (game->ray.width > x)
		game->ray.width = x;
	if (game->ray.height > y)
		game->ray.height = y;
}

void		bitmap(t_game *game)
{
	int pixel_x;

	pixel_x = -1;
	if (!(game->z_buffer = malloc(sizeof(double) * (game->ray.width + 1))))
		print_error("ERROR - memory allcated failed");
	if (!(game->sprite = malloc(sizeof(t_sprite))))
		print_error("ERROR - memory allcated failed");
	game->sprite->next = NULL;
	game->sprite->distance = 0;
	while (++pixel_x < game->ray.width)
	{
		game->ray.camera_x = 2 * pixel_x / (double)game->ray.width - 1;
		set_ray_info(&game->ray, &game->player);
		check_hit(&game->ray, &game->map, game->sprite, &game->player);
		calc_perp_dist(&game->ray, &game->player);
		set_draw_info(&game->draw, &game->ray);
		set_tex_info(game);
		buffering_pixels(game, pixel_x);
		game->z_buffer[pixel_x] = game->ray.perp_dist;
	}
	buffering_sprite(game);
}
