/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inssong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 18:12:00 by inssong           #+#    #+#             */
/*   Updated: 2021/03/04 17:13:33 by inssong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# include <stdlib.h>
# include <unistd.h>
# include "../libft/libft.h"

typedef struct		s_buff
{
	int				fd;
	struct s_buff	*next;
	char			buff[BUFFER_SIZE + 1];
}					t_buff;

int					get_next_line(int fd, char **line);
t_buff				*creat_buffer(int fd);
t_buff				*find_fd(int fd, t_buff *head);
int					read_buffer(t_buff **buffer, char **line);
int					expand(char **line);
void				remake_buffer(char *buffer, char *temp);
int					read_next_buffer(t_buff **buffer);
void				free_head(t_buff **head, int fd);

#endif
