/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inssong <inssong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 05:04:10 by inssong           #+#    #+#             */
/*   Updated: 2021/05/27 07:04:14 by inssong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_node			*create_node(void)
{
	t_node		*node;

	if (!(node = malloc(sizeof(t_node))))
		return (NULL);
	node->y = 0;
	node->line = NULL;
	node->next = NULL;
	return (node);
}

t_node			*next_node(t_node *curr)
{
	t_node		*next;

	next = create_node();
	curr->next = next;
	return (next);
}

void			add_node(t_node *axis, int value)
{
	while (axis->next)
		axis = axis->next;
	axis->next = create_node();
	axis->next->y = value;
}

void			add_sorted_sprite(t_sprite **sprite, t_ray *ray, double dist)
{
	t_sprite	*new_sprite;
	t_sprite	*pos;

	new_sprite = make_new_sprite(ray, dist);
	pos = *sprite;
	if (new_sprite->distance <= (*sprite)->distance)
		new_sprite->next = *sprite;
	if (new_sprite->distance <= (*sprite)->distance || *sprite == NULL)
	{
		*sprite = new_sprite;
		return ;
	}
	while (pos->next)
	{
		if (new_sprite->distance > pos->next->distance)
		{
			new_sprite->next = pos->next;
			pos->next = new_sprite;
			return ;
		}
		pos = pos->next;
	}
	pos->next = new_sprite;
}

t_sprite		*make_new_sprite(t_ray *ray, double distance)
{
	t_sprite	*new_sprite;

	new_sprite = malloc(sizeof(t_sprite));
	new_sprite->sprite_x = ray->map_x + 0.5;
	new_sprite->sprite_y = ray->map_y + 0.5;
	new_sprite->distance = distance;
	new_sprite->next = NULL;
	return (new_sprite);
}
