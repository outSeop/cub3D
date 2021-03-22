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

void			add_sprite(t_sprite *sprite, t_player *player, double x, double y)
{
	int			i;

	while (sprite->next)
	{
		sprite = sprite->next;
		i++;
	}
	sprite->next = malloc(sizeof(t_sprite));
	sprite = sprite->next;
	sprite->y = y;
	sprite->x = x;
	sprite->distance = pow((player->pos_x - sprite->x), 2) + pow((player->pos_y - sprite->y), 2);
	sprite->order = i;
	sprite->next = NULL;
}

void			sort_sprite(t_sprite *sprite)
{
	t_sprite	*temp;
	t_sprite	*idx;

	printf("%p\n", sprite);
}
