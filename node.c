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
		array[i] = list->line;
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
	if (sprite->next != NULL)
	{
		while (sprite->next)
			sprite = sprite->next;
		sprite->next = malloc(sizeof(t_sprite));
		sprite = sprite->next;
	}
	sprite->sprite_x = ray->map_x;
	sprite->sprite_y = ray->map_y;
	sprite->next = NULL;
}

void			sort_sprite(t_sprite *sprite)
{
	t_sprite	*temp;
	t_sprite	*head;
	t_sprite	*pre;

	head = malloc(sizeof(t_sprite));
	head->next = sprite;
	while (sprite->next)
	{
		if (sprite->distance < sprite->next->distance)
		{
			if (sprite->next->next)
				temp = sprite->next->next;
			else
				temp = NULL;
			sprite->next = sprite;
			sprite = temp;
			if (pre != NULL)
				pre->next = sprite;
			else
				head->next = sprite;
			sprite = head->next;
		}
		else
			sprite = sprite->next;
		pre = sprite;
	}
}

void		calc_sprite_distance(t_sprite *sprite, t_player *player)
{
	while (sprite->next)
	{
		sprite->distance = pow(player->pos_x - sprite->sprite_x, 2) + pow(player->pos_y - sprite->sprite_y, 2);
		sprite = sprite->next;
	}
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
