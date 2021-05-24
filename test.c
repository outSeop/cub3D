#include "cub3D.h"


int			main(int argc, char *argv[])
{
	t_game 	game;
	int		fd;

	if ((fd = error_input(argc, argv)) == -1)
		return (0);
	init_map(&game);
	init_player(&game);
	if (parsing_cub(&game.map, fd) == -1)
		print_error("1");
	if (!(parsing_map(fd, &game.player, &game.map.height, &game.map)))
		print_error("2");
	if (!check_map(game.map.map_visited, (int)game.player.pos_x, (int)game.player.pos_y, game.map.height))
		print_error("map eeorr\n");
	error_file(&game.map);
	game.ray.width = game.map.resolution[0];
	game.ray.height = game.map.resolution[1];
	// int x, y;
	// mlx_get_screen_size(game.vars.mlx, &x, &y);
	// if (game.ray.width > x)
	// 	game.ray.width = x;
	// if (game.ray.height > y)
	// 	game.ray.height = y;
	init_game(&game);
	if (game.player.check != 1)
	{
		printf("ERROR\n");
		return (0);
	}

	load_textures(&game);
	save_bitmap(&game);
	//engine(&game);
	start(&game);
}

void	save_bitmap(t_game *game)
{
	int				padding;
	int				filesize;
	int				file;

	padding = (4 - (game->ray.width * 3) % 4) % 4;
	filesize = 54 + ((padding + game->ray.width) * game->ray.height) * 3;
	file = open("screenshot.bmp", O_WRONLY | O_CREAT | O_TRUNC | O_APPEND);
	save_bitmap_header(game, padding, filesize,file);
	save_bitmap_data(game, file, padding);
}

void	save_bitmap_data(t_game *game, int file, int padding)
{
	int				i;
	int				j;
	int				color;

	i = 0;
	while (i < game->ray.height)
	{
		j = 0;
		while (j < game->ray.width)
		{
			color = get_color(game, j, i);
			write(file, &color, 3);
			write(file, &"000", padding);
			j++;
		}
		i++;
	}
}

int		get_color(t_game *game, int j, int i)
{
	int	rgb;
	int	color;

	color = *(int*)(game->stick.addr
			+ (4 * game->ray.width * (game->ray.height - 1 - i))
			+ (4 * j));
	rgb = (color & 0xFF0000) | (color & 0x00FF00) | (color & 0x0000FF);
	return (rgb);
}
void	save_bitmap_header(t_game *game, int padding, int filesize, int file)
{
	int				i;
	unsigned char	bitmap_header[54];

	i = 0;
	while (i < 54)
		bitmap_header[i++] = (unsigned char)0;
	bitmap_header[0] = (unsigned char)'B';
	bitmap_header[1] = (unsigned char)'M';
	set_int_in_char(bitmap_header + 2, filesize);
	bitmap_header[10] = (unsigned char)54;
	bitmap_header[14] = (unsigned char)40;
	set_int_in_char(bitmap_header + 18, game->ray.width);
	set_int_in_char(bitmap_header + 22, game->ray.height);
	bitmap_header[27] = (unsigned char)1;
	bitmap_header[28] = (unsigned char)24;
	write(file, bitmap_header, 54);
}

void	set_int_in_char(unsigned char *c, int i)
{
	c[0] = (unsigned char)(i);
	c[1] = (unsigned char)(i >> 8);
	c[2] = (unsigned char)(i >> 16);
	c[3] = (unsigned char)(i >> 24);
}
