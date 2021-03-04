/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inssong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 18:09:54 by inssong           #+#    #+#             */
/*   Updated: 2021/03/04 17:13:04 by inssong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void			remake_buffer(char *buffer, char *temp)
{
	int			i;

	i = 0;
	while (temp[i])
	{
		buffer[i] = temp[i];
		i++;
	}
	buffer[i] = '\0';
}

int				read_next_buffer(t_buff **buffer)
{
	int			size;

	if ((size = read((*buffer)->fd, (*buffer)->buff, BUFFER_SIZE)) <= 0)
		return (size);
	(*buffer)->buff[size] = '\0';
	return (size);
}

void			free_head(t_buff **buffer, int fd)
{
	t_buff		*pre;
	t_buff		*nxt;
	t_buff		*cur;

	cur = *buffer;
	nxt = cur->next;
	if (cur->fd == fd)
	{
		*buffer = nxt;
		free(cur);
		return ;
	}
	while (1)
	{
		pre = cur;
		cur = nxt;
		nxt = cur->next;
		if (cur->fd == fd)
		{
			pre->next = nxt;
			free(cur);
			return ;
		}
	}
	nxt->next = NULL;
}
