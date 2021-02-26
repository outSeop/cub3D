#include "cub3D.h"

#define WIDTH 640
#define HEIGHT 360



#define mapWidth 24
#define mapHeight 24

int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};



int				main(void)
{
	t_game		*game;


	game = init_game();
	game->vars.mlx = mlx_init();
	game->vars.win = mlx_new_window(game->vars.mlx, WIDTH, HEIGHT, "Hello world!");


	mlx_hook(game->vars.win, 2, 0, key_press, &(game->vars));
	mlx_hook(game->vars.win, 3, 0, key_release, &(game->vars));
	mlx_loop_hook(game->vars.mlx, main_loop, game);


	mlx_loop(game->vars.mlx);
}

int				main_loop(t_game *game)
{
	/*
	if (game->moving_forward)
		game->pos_x += 1;
	else if (game->moving_behind)
		game->pos_x -= 1;
	else if (game->turn_left)
		game->angle -= 1;
	else if (game->turn_right)
		game->angle += 1;
	printf("%d - %d\n", game->pos_x, game->angle);
	*/
	refresh_camera(game);
	return (0);
}

int				refresh_camera(t_game *game)
{
	t_data		img;
	int x;
	double posX = 22, posY = 12;
	double dirX = 2, dirY = -1;
	double planeX = 0, planeY = 0.66;
	int			w;

	x = 0;
	w = 100;
	while (x < w)
	{
		double		cameraX = 2 * x / (double)w - 1;
		double		rayDirX = dirX + planeX * cameraX;
		double		rayDirY = dirY + planeY * cameraX;
	int mapX = (int)posX;
	int mapY = (int)posY;

	double sideDistX;
	double sideDistY;

	double deltaDistX = fabs(1 / rayDirX);
	double deltaDistY = fabs(1 / rayDirY);
	double prepWallDist;

	int stepX;
	int stepY;

	int hit = 0;
	int side;

	if (rayDirX < 0)
	{
		stepX = -1;
		sideDistX = (posX - mapX) * deltaDistX;
	}
	else
	{
		stepX = 1;
		sideDistX = (mapX + 1.0 - posX) * deltaDistX;
	}
	if (rayDirY < 0)
	{
		stepY = -1;
		sideDistY = (posY - mapY) * deltaDistY;
	}
	else
	{
		stepY = 1;
		sideDistY = (mapY + 1.0 - posY) * deltaDistY;
	}

	while (hit == 0)
	{
		if (sideDistX < sideDistY)
		{
			sideDistX += deltaDistY;
			mapX += stepX;
			side = 0;
		}
		else
		{
			sideDistY += deltaDistY;
			mapY += stepY;
			side = 1;
		}
		if (worldMap[mapX][mapY] > 0 )
			hit = 1;
	}
	if (side == 0)
		prepWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
	else
		prepWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

	int h = HEIGHT;
	int lineHeight = (int)(h / prepWallDist);
	int drawStart = -lineHeight / 2 + h / 2;
	if (drawStart < 0)
		drawStart = 0;
	int drawEnd = lineHeight / 2 + h / 2;
	if (drawEnd >= h)
		drawEnd = h - 1;

	int color;
	if (worldMap[mapX][mapY] == 1)
		color = 0x00FF0000;
	else if (worldMap[mapX][mapY] == 2)
		color = 0x00AA0000;
	else if (worldMap[mapX][mapY] == 3)
		color = 0x00CC0000;
	else if (worldMap[mapX][mapY] == 4)
		color = 0x00DD0000;
	else
		color = 0x00000000;
	if (side == 1)
	 	color = color / 2;
	img.img = mlx_new_image(game->vars.mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	for (int i = drawStart; i < drawEnd; i++)
	{
		my_mlx_pixel_put(&img, 0, i, color);
	}
	mlx_put_image_to_window(game->vars.mlx, game->vars.win, img.img, x, 0);
	x++;
	}


}
int				key_press(int keycode, t_game *game)
{
	if (keycode == ESC)
		close_window(&(game->vars));
	else if (keycode == KEY_W)
		game->moving_forward = 1;
	else if (keycode == KEY_S)
		game->moving_behind = 1;
	else if (keycode == KEY_D)
		game->turn_right = 1;
	else if (keycode == KEY_A)
		game->turn_left = 1;

		return (0);
}

int				key_release(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->moving_forward = 0;
	else if (keycode == KEY_S)
		game->moving_behind = 0;
	else if (keycode == KEY_D)
		game->turn_right = 0;
	else if (keycode == KEY_A)
		game->turn_left = 0;

		return (0);
}

int				close_window(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
}

int				mouse_pos(int keycode, t_vars *vars)
{
}
void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

t_game			*init_game()
{
	t_game		*game;

	if (!(game = malloc(sizeof(t_game))))
		return (NULL);
	game->pos_x = 0;
	game->angle = 0;
	game->moving_forward = 0;
	game->moving_behind = 0;
	game->turn_left = 0;
	game->turn_right = 0;
	return ((void*)game);
}
