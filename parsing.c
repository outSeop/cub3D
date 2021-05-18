#include "cub3D.h"

int		parsing_cub(t_map *map, t_player *player, int fd)
{
	char	*line;
	int		check;

	check = 0;
	line = 0;
	while (get_next_line(fd, &line))
	{
		check += put_in_texture(map, line);
		if (check >= 8)
			break ;
		free(line);
	}
	free(line);
	return (error_file(map));
}

void		parsing_textures(t_map *map, int fd)
{
	printf("%s", map->textures[0]);
	printf("f%d", fd);

}

int			put_in_texture(t_map *map, char *line)
{
	int		i;
	char	*clean_str;
	char	*element;

	clean_str = ft_strtrim(line, SPACES);
	element = put_element(clean_str);
	i = ft_strlen(element);
	clean_str = clean_string(clean_str , i);
	if (!ft_strncmp(element, "R", i))
		save_res_info(map, clean_str);
	else if (!ft_strncmp(element, "F", i) && map->floor == 0)
		map->floor = save_map_info(clean_str);
	else if (!ft_strncmp(element, "C", i) && map->celling == 0)
		map->celling = save_map_info(clean_str);
	else if (!ft_strncmp(element, "NO", i) && !map->textures[NO])
		map->textures[NO] = save_path(clean_str);
	else if (!ft_strncmp(element, "SO", i) && !map->textures[SO])
		map->textures[SO] = save_path(clean_str);
	else if (!ft_strncmp(element, "WE", i) && !map->textures[WE])
		map->textures[WE] = save_path(clean_str);
	else if (!ft_strncmp(element, "EA", i) && !map->textures[EA])
		map->textures[EA] = save_path(clean_str);
	else if (!ft_strncmp(element, "S", i) && !map->textures[S])
		map->textures[S] = save_path(clean_str);
	free(element);
	free(clean_str);
	return (1);
}

char			*put_element(char *str)
{
	int			i;
	char		*res;
	char		*temp;

	if (!str[i])
		print_error("There is wrong\n");
	temp = malloc(3);
	i = 0;
	while (!ft_isspace(str[i])
	{
		temp[i] = str[i];
		i++;
		if (i > 3)
		{
			free(temp);
			return (NULL);
		}
	}
	temp[i] = '\0';
	return (temp);
}
char			*clean_string(char *str, int i)
{
	char		*clean_str;

	clean_str = ft_strtrim(str + i, SPACES);
	free(str);
	return (clean_str);
}
int				pass_space(char *line)
{
	int			i;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	return (i);
}

int				ft_isspace(char line)
{
	if (('\t' <= line && line <= '\r') || line == ' ')
		return (1);
	return (0);
}

char			*save_path(char *line)
{
	int		i;
	char	*clean_str;
	char	*res;

	i = 0;
	clean_str = ft_strtrim(line, SPACES);
	i = pass_space(clean_str + i);
	if (ft_strrchr(clean_str + i, ' ')) // Too Many arg
	{
		print_error("texture field error");
		exit(0); // XXX: error handler
	}
	res = ft_strdup(clean_str + i);
	free(clean_str);
	return (res);
}

int				save_map_info(char *line)
{
	int		i;
	int		res;
	char	**colors;

	i = 0;
	i = pass_space(line + i);
	colors = ft_split(line + i, ',');
	i = 0;
	res = create_trgb(0, ft_atoi(colors[0]), ft_atoi(colors[1]), ft_atoi(colors[2]));
	free_all(colors);
	return (res);
}

int				parsing_map(int fd, t_player *player, int *map_height, t_map *map)
{
	t_node		*node;
	t_node		*head;
	char		*line;
	int			gnl;

	*map_height = 0;
	head = create_node();
	node = head;
	while (get_next_line(fd, &line))
	{
		if (line[0] == 0)
			continue ;
		node = next_node(node);
		node->y = *map_height;
		node->line = ft_strdup(line);
		find_player(node->line, player, *map_height);
		(*map_height)++;
	}
	if (*map_height == 0)
		return (0);
	map->map = list_to_array(head->next, *map_height);
	map->map_visited = list_to_array(head->next, *map_height);
	free_node(head);
	return (1);
}

void			find_player(char *line, t_player *player, int num)
{
	int			i;

	i = 0;
	while (line[i])
	{
		if (!ft_strrchr(ALLOWED_TEXTS, line[i]))
			player->check = 999;
		else if (line[i] == 'N')
		{
			set_player_dir_info(player, -1, 0);
			set_player_pos_info(player, num, i);
			player->check++;
			line[i] = '0';
		}
		else if (line[i] == 'S')
		{
			set_player_dir_info(player, 1, 0);
			set_player_pos_info(player, num, i);
			player->check++;
			line[i] = '0';
		}
		else if (line[i] == 'W')
		{
			set_player_dir_info(player, 0, 1);
			set_player_pos_info(player, num, i);
			player->check++;
			line[i] = '0';
		}
		else if (line[i] == 'E')
		{
			set_player_dir_info(player, 0, -1);
			set_player_pos_info(player, num, i);
			player->check++;
			line[i] = '0';
		}
		i++;
	}
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

