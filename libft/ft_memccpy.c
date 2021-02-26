/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inssong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 15:41:21 by inssong           #+#    #+#             */
/*   Updated: 2020/10/31 18:06:56 by inssong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memccpy(void *d, const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*((unsigned char*)d + i) = *((unsigned char*)s + i);
		if (*((unsigned char*)s + i) == (unsigned char)c)
			return (d + i + 1);
		i++;
	}
	return (NULL);
}
