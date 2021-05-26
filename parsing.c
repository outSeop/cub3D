#include "cub3D.h"

int				parsing_cub(t_map *map, int fd)
{
	char		*line;
	int			check;

	check = 0;
	line = 0;
	while (get_next_line(fd, &line))
	{
		if (!line[0])
			continue;
		check += put_in_texture(map, line);
		if (check >= 8)
			break ;
		free(line);
	}
	free(line);
	return (error_file(map));
}

int				put_in_texture(t_map *map, char *line)
{
	int			i;
	char		*clean_str;
	char		*element;

	clean_str = ft_strtrim(line, SPACES);
	element = put_element(clean_str);
	i = ft_strlen(element);
	clean_str = clean_string(clean_str, i);
	if (check_texture(map, clean_str, element) == 0
		&& check_rfc(map, clean_str, element) == 0)
		print_error("Wrong");
	free(element);
	free(clean_str);
	return (1);
}

char			*put_element(char *str)
{
	int			i;
	char		*temp;

	if (str[0] == '\0')
		print_error("There is wrong\n");
	temp = malloc(3);
	i = 0;
	while (str[i] != ' ')
	{
		if (i > 2)
			print_error("ERROR - Wrong element");
		temp[i] = str[i];
		i++;
	}
	temp[i] = '\0';
	return (temp);
}

char			*save_path(char *line)
{
	int		i;
	char	*clean_str;
	char	*res;

	i = 0;
	clean_str = ft_strtrim(line, SPACES);
	i = pass_space(clean_str + i);
	if (ft_strrchr(clean_str + i, ' '))
	{
		print_error("texture field error");
		exit(0);
	}
	res = ft_strdup(clean_str + i);
	free(clean_str);
	return (res);
}

int				parsing_map(int fd, t_player *player, int *m_h, t_map *map)
{
	t_node		*node;
	t_node		*head;
	char		*line;

	head = create_node();
	node = head;
	while (get_next_line(fd, &line))
	{
		if (line[0] == 0 && *m_h > 0)
			return (0);
		if (!(line[0] == 0 && *m_h == 0))
		{
			node = next_node(node);
			node->line = ft_strdup(line);
			find_player(node->line, player, (*m_h)++);
		}
		free(line);
	}
	free(line);
	if (*m_h == 0)
		return (0);
	map->map = list_to_array(head->next, *m_h);
	map->map_visited = list_to_array(head->next, *m_h);
	free_node(head);
	return (1);
}
