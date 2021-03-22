#include "cub3D.h"

void			draw(t_game *game)
{
	int			y;
	int			x;

	y = 0;
	while (y < game->ray.height)
	{
		x = 0;
		while (x < game->ray.width)
		{
			game->stick.addr[y * game->ray.width + x] = game->draw_buffer[y * game->ray.width + x];
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(game->vars.mlx, game->vars.win, game->stick.img, 0, 0);
}
