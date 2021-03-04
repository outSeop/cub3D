#include "cub3D.h"

void		parsing_map(t_map *map, int fd)
{
	char	**line;

	while (1)
	{
		line = get_next_line(fd, line);
		pass_space(line);
		if (ft_strnstr(*line, "R", 1))
			map->resolution = save_map_info(line);
		else if (ft_strnstr(*(++line), "NO", 2))
			map->texture[NO] = save_path(line);
		else if (ft_strnstr(*(++line), "SO", 2))
			map->texture[SO] = save_path(line);
		else if (ft_strnstr(*(++line), "WE", 2))
			map->texture[WE] = save_path(line);
		else if (ft_strnstr(*(++line), "EA", 2))
			map->texture[EA] = save_path(line);
		else if (ft_strnstr(*(++line), "S", 1))
			map->texture[S] = save_path(line);
		else if (ft_strnstr(*(++line), "F", 1))
			map->floor = save_map_info(line);
		else if (ft_strnstr(*(++line), "C", 1))
			map->floor = save_map_info(line);
		else

	}

}

void			pass_space(char **line)
{
	while (find_space(*line))
		(*line)++;
}

int				find_space(char *line)
{
	if ('\r' < *line && *line < '\t' || *line == ' ')
		return (1);
	return (0);
}

void		save_path(char *line)
{
	int		i;

	i = 0;
	while (line[i])
		if (find_space(line[i]))
			i++;
		else
			break;

	return (ft_strdup(line));
}

void		save_map_info(char *line)
{
	int		i;

	i = 0;
	while (line[i])
		if (find_space(line[i++]))
			return (0);

}
