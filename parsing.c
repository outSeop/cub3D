#include "cub3D.h"

void		parsing_map(t_map *map, int fd)
{
	char	*line;
	char	*tmp;
	line = 0;
	while (get_next_line(fd, &line))
	{
		tmp = line;
		line += pass_space(line);
		if (ft_strnstr(line, "R", 1))
			printf("pass\n");
		else if (ft_strnstr(line, "NO", 2))
			map->textures[NO] = save_path(line);
		else if (ft_strnstr(line, "SO", 2))
			map->textures[SO] = save_path(line);
		else if (ft_strnstr(line, "WE", 2))
			map->textures[WE] = save_path(line);
		else if (ft_strnstr(line, "EA", 2))
			map->textures[EA] = save_path(line);
		else if (ft_strnstr(line, "S", 1))
			map->textures[S] = save_path(line);
		else if (ft_strnstr(line, "F", 1))
			map->floor = save_map_info(line);
		else if (ft_strnstr(line, "C", 1))
			map->celling = save_map_info(line);
		free(tmp);
	}
	free(line);

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

	i = 0;
	while (!ft_isspace(line[i]))
		i++;
	while (line[i])
		if (ft_isspace(line[i]))
			i++;
		else
			break;
	line = ft_strdup(line + i);
	return (line);
}

int				save_map_info(char *line)
{
	int		i;
	int		res;
	char	**colors;

	i = 0;
	while (!ft_isspace(line[i]))
		i++;
	while (line[i])
		if (ft_isspace(line[i]))
			i++;
		else
			break;
	colors = ft_split(line + i, ',');
	i = 0;
	while (colors[i])
		ft_strtrim(colors[i++], " \t\r");
	res = create_trgb(0, ft_atoi(colors[0]), ft_atoi(colors[1]), ft_atoi(colors[2]));
	i = 0;
	free(colors);
	return (res);
}
