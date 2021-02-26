/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inssong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 16:36:18 by inssong           #+#    #+#             */
/*   Updated: 2020/10/12 23:28:03 by inssong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*tmp;
	char	*s;

	if (dst == NULL && src == NULL)
		return (NULL);
	if (dst <= src)
	{
		tmp = (char*)dst;
		s = (char*)src;
		while (len--)
			*tmp++ = *s++;
	}
	else
	{
		tmp = (char*)dst;
		s = (char*)src;
		tmp += len;
		s += len;
		while (len--)
			*--tmp = *--s;
	}
	return (dst);
}
