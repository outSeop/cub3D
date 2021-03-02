#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include <math.h>
# include <stdio.h>
# include <mlx.h>


#define texWidth 64
#define texHeight 64

# define mapWidth 24
# define mapHeight 24

# define ESC 53
# define KEY_A 2
# define KEY_S 1
# define KEY_D 0
# define KEY_W 13

#define WIDTH 640
#define HEIGHT 360


# define PLAYER_START_POS_X 12
# define PLAYER_START_POS_Y 12
# define PLAYER_START_DIR_X 1
# define PLAYER_START_DIR_Y 0

# define MOVESPEED 0.1
# define TURNSPEED 0.07

int				g_check;
int				g_texture[8][texHeight * texWidth];

typedef struct s_stick
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_stick;

typedef struct s_vars
{
	void		*mlx;
	void		*win;
}				t_vars;

typedef struct s_img
{
	void		*img;
	char		*path;
	int 		img_width;
	int			img_height;
}				t_img;

typedef struct s_ray
{
	double		camera_x;
	double		dir_x;
	double		dir_y;
	int			map_x;
	int			map_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		prep_wall_dist;
	int			step_x;
	int			step_y;
	int			side;
	double		plane_x;
	double		plane_y;
}				t_ray;

typedef struct s_player
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
}				t_player;

typedef struct s_draw
{
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			color;
}				t_draw;

typedef struct	s_mouse
{
	int			pos_x;
	int			pos_y;
	int			playing;
}				t_mouse;

typedef struct s_game
{
	t_vars		vars;
	t_draw		draw;
	t_ray		ray;
	t_player	player;
	t_stick		stick;
	t_mouse		mouse;
	int			angle;
	int			moving_forward;
	int			moving_behind;
	int			turn_left;
	int			turn_right;
}				t_game;



void			my_mlx_pixel_put(t_stick *data, int x, int y, int color);
int				key_press(int keycode, t_game *game);
int				key_release(int keycode, t_game *game);
int				main_loop(t_game *game);
int				close_window(t_vars *vars);
int				create_trgb(int t, int r, int g, int b);
int				get_t(int trgb);
int				get_r(int trgb);
int				get_g(int trgb);
int				get_b(int trgb);
int				mouse_pos(int keycode, t_vars *vars);
int				refresh_camera(t_game *game);

void			start(t_game *game);
void			engine(t_game *game);

void			init_game(t_game *game);
void			init_vars(t_game *game);
void			init_draw(t_game *game);
void			init_player(t_game *game);
void			init_stick(t_game *game);
void			init_ray(t_game *game);

void			print_init(t_game *game);
int				catch_mouse_move();
void			get_mouse_pos(t_game *game);
void			hide_mouse_pointer(t_game *game);
void			hold_in_senter(t_game *gmae);


void			make_texture();

#endif
