#include "cub3D.h"
void			init_game(t_game *game)
{

	game->angle = 0;
	game->moving_forward = 0;
	game->moving_behind = 0;
	game->turn_left = 0;
	game->turn_right = 0;
	init_player(game);
	init_draw(game);
	init_vars(game);
	init_stick(game);
	init_ray(game);

}

void			init_draw(t_game *game)
{
	game->draw.line_height = 0;
	game->draw.draw_start = 0;
	game->draw.draw_end = 0;
	game->draw.color = 0x00000000;
}

void			init_player(t_game *game)
{
	game->player.pos_x = PLAYER_START_POS_X;
	game->player.pos_y = PLAYER_START_POS_Y;
	game->player.dir_x = PLAYER_START_DIR_X;
	game->player.dir_y = PLAYER_START_DIR_Y;
}

void			init_ray(t_game *game)
{
	game->ray.camera_x = 0;
	game->ray.dir_x = -1;
	game->ray.dir_y =0;
	game->ray.map_x = 0;
	game->ray.map_y = 0;
	game->ray.side_dist_x = 0;
	game->ray.side_dist_y = 0;
	game->ray.delta_dist_x = 0;
	game->ray.delta_dist_y = 0;
	game->ray.prep_wall_dist = 0;
	game->ray.step_x = 0;
	game->ray.step_y = 0;
	game->ray.side = 0;
	game->ray.plane_x = 0;
	game->ray.plane_y = 0.66;
}

void			init_stick(t_game *game)
{
	game->stick.img = mlx_new_image(game->vars.mlx, WIDTH, HEIGHT);
	game->stick.addr = mlx_get_data_addr(game->stick.img, &game->stick.bits_per_pixel ,&game->stick.line_length, &game->stick.endian);
}

void			init_vars(t_game *game)
{
	game->vars.mlx = mlx_init();
	game->vars.win = mlx_new_window(game->vars.mlx, WIDTH, HEIGHT, "title");
}

void			print_init(t_game *game)
{
	printf("%f\n", game->player.pos_x);
}
