/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inssong <inssong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 05:03:28 by inssong           #+#    #+#             */
/*   Updated: 2021/05/27 09:06:12 by inssong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include "gnl/get_next_line.h"
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include "mlx/mlx.h"

# define ALL_DIRECTIONS "NSEW"
# define ALLOWED_TEXTS "012 WSEN"

# define SPACES " \n\t\v\f\r"
# define ESC 53
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_W 13
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define HX "2213"
# define HY "1322"

# define MOVESPEED 0.050000001
# define T_SPEED 0.050137

# define NO 0
# define SO 1
# define WE 2
# define EA 3
# define S 4
# define R 5
# define F 6
# define C 7

typedef struct		s_spinfo
{
	double			sprite_x;
	double			sprite_y;
	double			inv_det;
	double			transform_x;
	double			transform_y;
	int				sprite_width;
	int				sprtie_screen_x;
	int				sprite_height;
	int				draw_start_x;
	int				draw_end_x;
	int				draw_start_y;
	int				draw_end_y;
	int				tex_x;
	int				tex_y;
}					t_spinfo;

typedef struct		s_stick
{
	void			*img;
	int				*addr;
	int				width;
	int				height;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_stick;

typedef struct		s_vars
{
	void			*mlx;
	void			*win;
}					t_vars;

typedef struct		s_ray
{
	double			camera_x;
	double			dir_x;
	double			dir_y;
	int				map_x;
	int				map_y;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			perp_dist;
	int				step_x;
	int				step_y;
	int				side;
	double			plane_x;
	double			plane_y;
	int				width;
	int				height;
	int				direction;
	int				num_sprite;
	int				map_size;
}					t_ray;

typedef struct		s_player
{
	int				jump;
	int				check;
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
}					t_player;

typedef struct		s_draw
{
	int				line_height;
	int				draw_start;
	int				draw_end;
	int				color;
}					t_draw;

typedef struct		s_map
{
	char			**map;
	char			**map_visited;
	char			*textures[5];
	int				resolution[2];
	int				floor;
	int				celling;
	int				height;
	int				chk_dp[8];
}					t_map;

typedef struct		s_node
{
	int				y;
	char			*line;
	struct s_node	*next;
}					t_node;

typedef struct		s_texture
{
	int				num;
	int				**tex;
	int				tex_height[5];
	int				tex_width[5];
	int				tex_x;
	int				tex_y;
	double			step;
	double			wall_x;
	double			tex_pos;
}					t_texture;

typedef struct		s_sprite
{
	double			sprite_x;
	double			sprite_y;
	double			distance;
	struct s_sprite	*pre;
	struct s_sprite *next;
}					t_sprite;

typedef struct		s_game
{
	t_vars			vars;
	t_draw			draw;
	t_ray			ray;
	t_player		player;
	t_stick			stick;
	t_texture		tex;
	t_map			map;
	t_sprite		*sprite;
	t_spinfo		spinfo;
	int				angle;
	int				moving_forward;
	int				moving_behind;
	int				moving_left;
	int				moving_right;
	int				turn_left;
	int				turn_right;
	double			*z_buffer;
	int				sc;
}					t_game;

void				buffering_sprite(t_game *game);

void				load_textures(t_game *game);

void				my_mlx_pixel_put(t_stick *data, int x, int y, int color);
int					key_press(int keycode, t_game *game);
int					key_release(int keycode, t_game *game);
int					main_loop(t_game *game);
int					close_window(t_vars *vars);
int					create_trgb(int t, int r, int g, int b);
int					refresh_camera(t_game *game);

void				start(t_game *game);
void				engine(t_game *game);

void				set_ray_info(t_ray *ray, t_player *player);
void				check_hit(t_ray *ray, t_map *map
						, t_sprite *sprite, t_player *player);
void				set_draw_info(t_draw *draw, t_ray *ray);
void				set_tex_info(t_game *game);
void				buffering_pixels(t_game *game, int pixel_x);

void				init_game(t_game *game);
void				init_vars(t_game *game);
void				init_draw(t_game *game);
void				init_player(t_game *game);
void				init_stick(t_game *game);
void				init_ray(t_game *game);
void				init_map(t_game *game);

int					parsing_cub(t_map *map, int fd);
int					parsing_map(int fd, t_player *player
						, int *map_height, t_map *map);
void				find_player(char *line, t_player *player, int num);
void				save_res_info(t_map *map, char *line);
void				set_player_dir_info(t_player *player, int dir_x, int dir_y);
void				set_player_pos_info(t_player *player, int pos_x, int pos_y);
int					pass_space(char *line);
int					ft_isspace(char line);
char				*save_path(char *line, int *idx);
int					save_map_info(char *line, int *idx);
int					put_in_texture(t_map *map, char *line);
char				**free_all(char **line);
char				*put_element(char *str);
char				*clean_string(char *str, int i);

t_node				*create_node();
t_node				*next_node(t_node *curr);
char				**list_to_array(t_node *list, int size);
void				free_node(t_node *node);

void				calc_perp_dist(t_ray *ray, t_player *player);
void				make_texture(t_game *game, int i);

int					check_map(char **map, int x, int y, int map_height);
void				add_node(t_node *axis, int value);
void				add_sprite(t_sprite *sprite, t_ray *ray);
void				calc_sprite_distance(t_sprite *sprite, t_player *player);
void				sort_sprite(t_sprite *sprit);
void				free_sprite(t_sprite *sprite);
t_sprite			*add_sprite_front(t_sprite *sprite, t_ray *ray);
void				reset_map(t_map *map);

void				add_sorted_sprite(t_sprite **sprite
						, t_ray *ray, double distance);
int					find_zero(char **map, int *y, int *x);
int					bfs(t_node *node_y, t_node *node_x
						, char **map, int map_height);
char				add_nodes(t_node *ny, t_node *nx, int y, int x);
int					error_input(int argc, char *argv[], int *sc);
int					print_error(char *error);
int					error_file(t_map *map);

int					save_bitmap(t_game *game);
void				set_int_in_char(unsigned char *c, int i);
void				save_bitmap_header(t_game *game, int filesize, int file);
int					get_color(t_game *game, int j, int i);
void				save_bitmap_data(t_game *game, int file, int padding);

void				move_fb(t_game *g);
void				move_rl(t_game *g);
void				turn_rl(t_game *g);

t_sprite			*make_new_sprite(t_ray *ray, double distance);
void				calc_forward_aixs(t_ray *ray);
void				calc_sprite_xy(t_game *game);
void				calc_draw_start_end(t_game *game);
void				buffering_sprite_pixel(t_game *game
						, t_spinfo *s, t_texture *t);

void				prepare(t_game *game, int argc, char *argv[]);
// void				limit(t_game *game);
int					check_texture(t_map *map, char *clean_str, char *element);
int					check_rfc(t_map *map, char *clean_str, char *element);

void				reset(t_game *game);
void				find_player(char *line, t_player *player, int num);
int					check_valid_color(char **colors);
int					check_sc(char *argv);
void				bitmap(t_game *game);

int					com_max(int a, int b);
int					is_space(char c);
int					check_out(int y, int x, t_game *g);
void				check_comma(char *line);

int					finish(t_game *game);
#endif
