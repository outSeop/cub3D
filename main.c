#include "cub3D.h"

#define WIDTH 640
#define HEIGHT 360

int				main(void)
{
	t_vars		vars;
	t_data		img;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "Hello world!");
	img.img = mlx_new_image(vars.mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	my_mlx_pixel_put(&img, WIDTH / 2, HEIGHT / 2, 0x00FF0000);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_hook(vars.win, 2, 1L<<0, key_hook,  &vars);
	mlx_mouse_move(vars.win, 0, 0);
	mlx_loop(vars.mlx);


}

void			my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char		*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int				key_hook(int keycode, t_vars *vars)
{
	if (keycode == ESC)
		close_window(vars);
	else if (keycode == KEY_W)
		printf("W\n");
	else if (keycode == KEY_A)
		printf("A\n");
	else if (keycode == KEY_S)
		printf("S\n");
	else if (keycode == KEY_D)
		printf("D\n");
	else if (keycode == 3)
		mlx_mouse_hide();
	else if (keycode == 5)
		mlx_mouse_show();
	printf("%d\n", keycode);
}

int				close_window(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
}
