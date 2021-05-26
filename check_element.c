#include "cub3D.h"

int				check_texture(t_map *map, char *clean_str, char *element)
{
	int			i;

	i = ft_strlen(element);
	if (!ft_strncmp(element, "NO", i) && !map->textures[NO])
		map->textures[NO] = save_path(clean_str);
	else if (!ft_strncmp(element, "SO", i) && !map->textures[SO])
		map->textures[SO] = save_path(clean_str);
	else if (!ft_strncmp(element, "WE", i) && !map->textures[WE])
		map->textures[WE] = save_path(clean_str);
	else if (!ft_strncmp(element, "EA", i) && !map->textures[EA])
		map->textures[EA] = save_path(clean_str);
	else if (!ft_strncmp(element, "S", i) && !map->textures[S])
		map->textures[S] = save_path(clean_str);
	else
		return (0);
	return (1);
}

int				check_rfc(t_map *map, char *clean_str, char *element)
{
	int			i;

	i = ft_strlen(element);
	if (!ft_strncmp(element, "R", i))
		save_res_info(map, clean_str);
	else if (!ft_strncmp(element, "F", i) && map->floor == 0)
		map->floor = save_map_info(clean_str);
	else if (!ft_strncmp(element, "C", i) && map->celling == 0)
		map->celling = save_map_info(clean_str);
	else
		return (0);
	return (1);
}

void			set_player_dir_info(t_player *player, int dir_x, int dir_y)
{
	player->dir_x = dir_x;
	player->dir_y = dir_y;
}

void			set_player_pos_info(t_player *player, int pos_x, int pos_y)
{
	player->pos_x = pos_x + 0.5;
	player->pos_y = pos_y + 0.5;
}
