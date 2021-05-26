/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_element.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inssong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 05:03:14 by inssong           #+#    #+#             */
/*   Updated: 2021/05/27 05:03:15 by inssong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int				check_texture(t_map *map, char *clean_str, char *element)
{
	int			i;

	i = ft_strlen(element);
	if (!ft_strncmp(element, "NO", com_max(2, i)))
		map->textures[NO] = save_path(clean_str, &map->chk_dp[NO]);
	else if (!ft_strncmp(element, "SO", com_max(2, i)))
		map->textures[SO] = save_path(clean_str, &map->chk_dp[SO]);
	else if (!ft_strncmp(element, "WE", com_max(2, i)))
		map->textures[WE] = save_path(clean_str, &map->chk_dp[WE]);
	else if (!ft_strncmp(element, "EA", com_max(2, i)))
		map->textures[EA] = save_path(clean_str, &map->chk_dp[EA]);
	else if (!ft_strncmp(element, "S", com_max(1, i)))
		map->textures[S] = save_path(clean_str, &map->chk_dp[S]);
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
		map->floor = save_map_info(clean_str, &map->chk_dp[F]);
	else if (!ft_strncmp(element, "C", i) && map->celling == 0)
		map->celling = save_map_info(clean_str, &map->chk_dp[C]);
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

int				com_max(int a, int b)
{
	if (a > b)
		return (a);
	else
		return (b);
}
