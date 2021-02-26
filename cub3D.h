#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include <mlx.h>

# define ESC 53
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_W 13

typedef struct s_data
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_data;

typedef struct s_vars
{
	void		*mlx;
	void		*win;
}				t_vars;

void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
int				key_hook(int keycode, t_vars *vars);
int				close_window(t_vars *vars);
int				create_trgb(int t, int r, int g, int b);
int				get_t(int trgb);
int				get_r(int trgb);
int				get_g(int trgb);
int				get_b(int trgb);

#endif
