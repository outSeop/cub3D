#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include "gnl/get_next_line.h"
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <mlx.h>


# define TEX_WIDTH 64
# define TEX_HEIGHT 64

# define All_DIRECTIONS "WSEN"

# define mapWidth 24
# define mapHeight 24

# define SPACES "\t\r "
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

# define NO 0
# define SO 1
# define WE 2
# define EA 3
# define S 4
# define R 5
# define F 6
# define C 7

int				g_check;
int				g_texture[8][TEX_HEIGHT * TEX_WIDTH + 1];

typedef struct s_vector
{
	double		first;
	int			second;
}				t_vector;

typedef struct s_stick
{
	void		*img;
	int			*addr;
	int			width;
	int			height;
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
	double		perp_dist;
	int			step_x;
	int			step_y;
	int			side;
	double		plane_x;
	double		plane_y;
	int			width;
	int			height;
	int			tex;
}				t_ray;

typedef struct s_player
{
	int			jump;
	int			check;
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

typedef struct s_map
{
	char		**map;
	char		*textures[5];
	int			resolution[2];
	int			floor;
	int			celling;
	int			height;
}				t_map;

typedef struct s_node
{
	int			y;
	char		*line;
	struct s_node *next;
}				t_node;

typedef struct	s_mouse
{
	int			pos_x;
	int			pos_y;
	int			playing;
}				t_mouse;

typedef struct s_texture
{
	int			num;
	int			tex_x;
	int			tex_y;
	double		step;
	double		wall_x;
	double		tex_pos;
}				t_texture;

typedef struct s_sprite
{
	int			order;
	double		distance;
	double		x;
	double		y;
	struct s_sprite *next;
}				t_sprite;

typedef struct s_game
{
	t_vars		vars;
	t_draw		draw;
	t_ray		ray;
	t_player	player;
	t_stick		stick;
	t_mouse		mouse;
	t_texture	tex;
	t_map		map;
	t_sprite	*sprite;
	double		*z_buffer;
	int			angle;
	int			moving_forward;
	int			moving_behind;
	int			turn_left;
	int			turn_right;
	int			*draw_buffer;
}				t_game;


void			draw(t_game *game);

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

void		set_base_info(t_game *game);
void			start(t_game *game);
void			engine(t_game *game);

void			set_ray_info(t_ray *ray, t_player *player);
void			check_hit(t_ray *ray, t_map *map, t_player *player, t_sprite *sprite);
void			calc_perp_dist(t_ray *ray, t_player *player);
void			set_draw_info(t_draw *draw, t_ray *ray);
void			set_tex_info(t_game *game);
void			buffering_pixels(t_game *game, int pixel_x);

void			init_game(t_game *game);
void			init_vars(t_game *game);
void			init_draw(t_game *game);
void			init_player(t_game *game);
void			init_stick(t_game *game);
void			init_ray(t_game *game);
void			init_map(t_game *game);

void			print_init(t_game *game);
int				catch_mouse_move();
void			get_mouse_pos(t_game *game);
void			hide_mouse_pointer(t_game *game);
void			hold_in_senter(t_game *gmae);

void			parsing_cub(t_map *map, t_player *player, int fd);
char			**parsing_map(int fd, t_player *player, int *map_height);
void			find_player(char *line, t_player *player, int num);
void	save_res_info(t_map *map, char *line);
void			set_player_dir_info(t_player *player, int dir_x, int dir_y);
void			set_player_pos_info(t_player *player, int pos_x, int pos_y);
int				pass_space(char *line);
int				ft_isspace(char line);
char			*save_path(char *line);
int				save_map_info(char *line);
int				put_in_texture(t_map *map, char *line);
char			**free_all(char **line);
void			jump(t_game *game);

t_node			*create_node();
t_node			*next_node(t_node *curr);
char			**list_to_array(t_node *list, int size);
void			sort_sprite(t_sprite *sprite);
void			add_sprite(t_sprite *sprite, t_player *player, double x, double y);

void	buffer(t_game *game);
void			make_texture(t_game *game, int i);
void		load_textures(t_game *game);

int			check_map(char **map, int x, int y, int map_height);
void			add_node(t_node *axis, int value);

#endif
