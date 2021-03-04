#include "cub3D.h"
void			make_texture()
{
	int			x;
	int			y;
	int			xorcolor;
	int			ycolor;
	int			xycolor;

	x = 0;
	while (x < 64)
	{
	y = 0;
		while (y < 64)
		{
			xorcolor = (x * 256 / 64) ^ (y * 256 / 64);
			ycolor = y * 256 / 64;
			xycolor = y * 128 / 64 + x * 128 / 64;
			g_texture[0][TEX_WIDTH * y + x] = 65536 * 254 * (x != y && x != TEX_WIDTH - y);
 			g_texture[1][TEX_WIDTH * y + x] = xycolor + 256 * xycolor + 65536 * xycolor;
			g_texture[2][TEX_WIDTH * y + x] = 256 * xycolor + 65536 * xycolor;
			g_texture[3][TEX_WIDTH * y + x] = xorcolor + 256 * xorcolor + 65536 * xorcolor;
			g_texture[4][TEX_WIDTH * y + x] = 256 * xorcolor;
			g_texture[5][TEX_WIDTH * y + x] = 65536 * 192 * (x % 16 && y % 16);
			g_texture[6][TEX_WIDTH * y + x] = 65536 * ycolor;
			g_texture[7][TEX_WIDTH * y + x] = 128 + 256 * 128 + 65536 * 128;
			y++;
		}
		x++;
	}
}
