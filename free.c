/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inssong <inssong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 05:03:47 by inssong           #+#    #+#             */
/*   Updated: 2021/05/27 07:04:12 by inssong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char			**free_all(char **line)
{
	int			i;

	i = 0;
	while (line[i])
	{
		free(line[i]);
		i++;
	}
	free(line);
	return (NULL);
}

void			free_sprite(t_sprite *sprite)
{
	t_sprite	*next;

	while (sprite->next)
	{
		next = sprite->next;
		free(sprite);
		sprite = next;
	}
	free(sprite);
}

void			free_node(t_node *node)
{
	t_node		*next;

	while (node->next)
	{
		next = node->next;
		free(node->line);
		free(node);
		node = next;
	}
	free(node->line);
	free(node);
}
