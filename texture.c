#include "cub3D.h"

void		make_texture(t_game *game, int i)
{
	int		y;
	int		x;

	game->stick.img = mlx_xpm_file_to_image(game->vars.mlx, game->map.textures[i], &game->stick.width, &game->stick.height);
	game->stick.addr = (int*)mlx_get_data_addr(game->stick.img, &game->stick.bits_per_pixel, &game->stick.line_length, &game->stick.endian);
	mlx_put_image_to_window(game->vars.mlx, game->vars.win, game->stick.img, 0, 0);
	printf("%d\n", i);
	y = 0;
	while (y < game->stick.height)
	{
		x = 0;
		while (x < game->stick.width)
		{
			g_texture[i][game->stick.width * y + x] = game->stick.addr[game->stick.width * y + x];
			x++;
		}
		y++;
	}
	mlx_destroy_image(game->vars.mlx, game->stick.img);
	init_stick(game);

}

void		load_textures(t_game *game)
{
	int		i;

	i = 0;
	while (i < 4)
		make_texture(game, i++);
}
