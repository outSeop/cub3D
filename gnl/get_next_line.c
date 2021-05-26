/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inssong <inssong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 18:08:25 by inssong           #+#    #+#             */
/*   Updated: 2021/05/26 11:58:32 by inssong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int					get_next_line(int fd, char **line)
{
	static t_buff	*head = NULL;
	t_buff			*temp_buffer;
	int				res;

	if (BUFFER_SIZE < 1 || fd < 0 || !line)
		return (-1);
	*line = 0;
	if ((!head && !(head = creat_buffer(fd)))
			|| !(temp_buffer = find_fd(fd, head)))
		return (-1);
	while (1)
	{
		if ((res = read_buffer(&temp_buffer, line)))
			return (res);
		res = read_next_buffer(&temp_buffer);
		if (res < 0)
		{
			*line = 0;
			return (-1);
		}
		if (!res)
			break ;
	}
	free_head(&head, fd);
	return (0);
}

t_buff				*creat_buffer(int fd)
{
	t_buff			*temp;

	if (!(temp = malloc(sizeof(t_buff))))
		return (NULL);
	temp->fd = fd;
	temp->buff[0] = '\0';
	temp->next = NULL;
	return (temp);
}

t_buff				*find_fd(int fd, t_buff *head)
{
	if (head->fd == fd)
		return (head);
	if (head->next == NULL)
		return (head->next = creat_buffer(fd));
	return (find_fd(fd, head->next));
}

int					read_buffer(t_buff **buffer, char **line)
{
	int				i;
	int				size;
	char			*temp;

	if ((size = expand(line)) == -1)
		return (-1);
	temp = (*buffer)->buff;
	i = 0;
	while (temp[i])
	{
		if (temp[i] == '\n')
		{
			remake_buffer((*buffer)->buff, temp + i + 1);
			(*line)[size + i] = '\0';
			return (1);
		}
		(*line)[size + i] = temp[i];
		i++;
	}
	(*line)[size + i] = '\0';
	return (0);
}

int					expand(char **line)
{
	char			*temp;
	int				i;
	int				size;

	i = 0;
	temp = *line;
	size = ft_strlen(*line);
	if (!(temp = malloc(size + BUFFER_SIZE + 1)))
		return (-1);
	while (i < size)
	{
		temp[i] = (*line)[i];
		i++;
	}
	free(*line);
	*line = temp;
	return (i);
}
