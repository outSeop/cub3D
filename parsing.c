/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inssong <inssong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 05:04:14 by inssong           #+#    #+#             */
/*   Updated: 2021/05/27 07:04:14 by inssong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		print_error("ERROR - Wrong element");
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
	while (str[i] != ' ' && str[i])
	{
		if (i > 2)
			print_error("ERROR - Wrong element");
		temp[i] = str[i];
		i++;
	}
	if (i == 0)
		print_error("ERROR - There is no texture element");
	temp[i] = '\0';
	return (temp);
}

char			*save_path(char *line, int *idx)
{
	char	*clean_str;
	char	*res;

	(*idx)++;
	if ((*idx) > 1)
		print_error("ERROR - Duplicate texture");
	if (line[0] == '\0')
		print_error("ERROR - There is no file path");
	clean_str = ft_strtrim(line, SPACES);
	res = ft_strdup(clean_str);
	free(clean_str);
	if (ft_strncmp(res + (ft_strlen(res) - 4), ".xpm", 4))
		print_error("ERROR - Wrong texture file format");
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
