/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inssong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 15:49:22 by inssong           #+#    #+#             */
/*   Updated: 2020/11/16 21:24:43 by inssong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *d, const char *s, size_t dsize)
{
	size_t	i;
	size_t	j;
	size_t	d_len;
	size_t	result;

	d_len = ft_strlen(d);
	result = ft_strlen(s);
	i = 0;
	j = d_len;
	if (dsize < d_len)
		return (dsize + result);
	while (*(s + i) != '\0' && i + d_len + 1 < dsize)
	{
		*(d + j) = *(s + i);
		j++;
		i++;
	}
	*(d + j) = '\0';
	result += d_len;
	return (result);
}
