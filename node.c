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
