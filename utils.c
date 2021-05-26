/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inssong <inssong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 05:04:47 by inssong           #+#    #+#             */
/*   Updated: 2021/05/27 07:04:17 by inssong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char			**list_to_array(t_node *list, int size)
{
	int			i;
	char		**array;

	if (!(array = malloc(sizeof(char**) * (size + 1))))
		return (NULL);
	i = 0;
	while (list)
	{
		array[i] = ft_strdup(list->line);
		i++;
		list = list->next;
	}
	array[i] = NULL;
	return (array);
}

int				create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
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

char			*clean_string(char *str, int i)
{
	char		*clean_str;

	clean_str = ft_strtrim(str + i, SPACES);
	free(str);
	return (clean_str);
}
