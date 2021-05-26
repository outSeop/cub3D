#include "cub3D.h"

void	save_bitmap(t_game *game)
{
	int				padding;
	int				filesize;
	int				file;

	padding = (4 - (game->ray.width * 3) % 4) % 4;
	filesize = 54 + ((padding + game->ray.width) * game->ray.height) * 3;
	file = open("screenshot.bmp"
		, O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, S_IRWXU);
	save_bitmap_header(game, padding, filesize, file);
	save_bitmap_data(game, file, padding);
}

void	save_bitmap_data(t_game *game, int file, int padding)
{
	int				i;
	int				j;
	int				color;

	i = game->ray.height - 1;
	while (i >= 0)
	{
		j = 0;
		while (j < game->ray.width)
		{
			color = get_color(game, i, j);
			write(file, &color, 3);
			write(file, &"000", padding);
			j++;
		}
		i--;
	}
}

int		get_color(t_game *game, int i, int j)
{
	int	rgb;
	int	color;

	color = *(game->stick.addr + ((i * game->stick.line_length
		+ j * (game->stick.bits_per_pixel / 8)) / 4));
	rgb = (color & 0xFF0000) | (color & 0x00FF00) | (color & 0x0000FF);
	printf("%x\n", rgb);
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
	bitmap_header[26] = (unsigned char)1;
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
