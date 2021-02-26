/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inssong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 21:23:15 by inssong           #+#    #+#             */
/*   Updated: 2020/11/16 19:52:09 by inssong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcpy(char *d, const char *s, size_t dsize)
{
	size_t	i;
	size_t	res;

	res = ft_strlen(s);
	i = 0;
	if (dsize)
	{
		while (*(s + i) && i < dsize - 1)
		{
			*(d + i) = *(s + i);
			i++;
		}
		*(d + i) = '\0';
	}
	return (res);
}
