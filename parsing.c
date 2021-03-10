#include "cub3D.h"

void		parsing_cub(t_map *map, int fd)
{
	char	*line;
	int		check;

	check = 0;
	line = 0;
	while (get_next_line(fd, &line))
	{
		if (check < 8)
			check += put_in_texture(map, line);
		else
			break ;
	}
	map->map = parsing_map(fd);
	printf("end\n");
}

void		parsing_textures(t_map *map, int fd)
{
	printf("%s", map->textures[0]);
	printf("f%d", fd);

}

int			put_in_texture(t_map *map, char *line)
{
	int		i;
	char	element[3];

	line = ft_strtrim(line, SPACES);
	i = 0;
	while (!ft_isspace(*line))
	{
		element[i] = *line;
		line++;
		i++;
	}
	element[i] = '\0';
	if (!ft_strncmp(element, "R", i))
		printf("element: %s\n", element);
	else if (!ft_strncmp(element, "F", i) && map->floor == 0)
		map->floor = save_map_info(line);
	else if (!ft_strncmp(element, "C", i) && map->celling == 0)
		map->celling = save_map_info(line);
	else if (!ft_strncmp(element, "NO", i) && !map->textures[NO])
		map->textures[NO] = save_path(line);
	else if (!ft_strncmp(element, "SO", i) && !map->textures[SO])
		map->textures[SO] = save_path(line);
	else if (!ft_strncmp(element, "WE", i) && !map->textures[WE])
		map->textures[WE] = save_path(line);
	else if (!ft_strncmp(element, "EA", i) && !map->textures[EA])
		map->textures[EA] = save_path(line);
	else if (!ft_strncmp(element, "S", i) && !map->textures[S])
		map->textures[S] = save_path(line);
	return (1);
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
	line = ft_strtrim(line, SPACES);
	i = pass_space(line + i);
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
	i = pass_space(line + i);
	colors = ft_split(line + i, ',');
	i = 0;
	/*
	while (colors[i])
		ft_strtrim(colors[i++], SPACES);
	*/
	res = create_trgb(0, ft_atoi(colors[0]), ft_atoi(colors[1]), ft_atoi(colors[2]));
	free(colors);
	return (res);
}

char			**parsing_map(int fd)
{
	char		**lines = NULL;
	char		**temp;
	char		*line;
	int			i;
	int			j;

	i = 0;
	while (get_next_line(fd, &line))
	{
		lines = malloc(sizeof(char**) * i);
		j = 0;
		while (lines[j])
		{
			temp[j] = lines[j];
			j++;
		}
		temp[i] = ft_strdup(line);
		lines = temp;
		i++;
	}
	return (lines);
}

char			**free_all(char **line)
{
	int			i;

	i = 0;
	while (*(line + i))
		free(line + i++);
	free(line);
	return (NULL);
}
