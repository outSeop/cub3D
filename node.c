#include "cub3D.h"
t_node			*create_node()
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

void			add_node(t_node *axis, int value)
{
	while (axis->next)
		axis = axis->next;
	axis->next = create_node();
	axis->next->y = value;
}

void			add_sprite(t_sprite *sprite, t_ray *ray)
{
	if (sprite->sprite_x != -1)
	{
		while (sprite->next)
			sprite = sprite->next;
		sprite->next = malloc(sizeof(t_sprite));
		sprite->next->pre = sprite;
		sprite = sprite->next;
	}
	sprite->sprite_x = ray->map_x + 0.5;
	sprite->sprite_y = ray->map_y + 0.5;
	sprite->next = NULL;
}

void		add_sorted_sprite(t_sprite **sprite, t_ray *ray, double distance)
{
	t_sprite	*new_sprite;
	t_sprite	*pos;

	new_sprite = malloc(sizeof(t_sprite));
	new_sprite->sprite_x = ray->map_x + 0.5;
	new_sprite->sprite_y = ray->map_y + 0.5;
	new_sprite->distance = distance;
	new_sprite->next = NULL;
	pos = *sprite;
	if (*sprite == NULL)
		*sprite = new_sprite;
	else if (new_sprite->distance <= (*sprite)->distance)
	{
		new_sprite->next = *sprite;
		*sprite = new_sprite;
	}
	else
	{
		while (1)
		{
			if (pos->next == NULL)
			{
				pos->next = new_sprite;
				break ;
			}
			else if (new_sprite->distance > pos->next->distance)
			{
				new_sprite->next = pos->next;
				pos->next = new_sprite;
				break ;
			}
			pos = pos->next;
		}
	}

}




void		calc_sprite_distance(t_sprite *sprite, t_player *player)
{
	t_sprite *head;
	double a, b;

	head = sprite;
	while (sprite)
	{
		a = pow(player->pos_x - sprite->sprite_x, 2);
		b = pow(player->pos_y - sprite->sprite_y, 2);
		sprite->distance = a + b;
		sprite = sprite->next;
	}
	sprite = head;
}

void		free_sprite(t_sprite *sprite)
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

void		free_node(t_node *node)
{
	t_node	*next;

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
