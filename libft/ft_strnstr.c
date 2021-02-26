/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inssong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 16:54:28 by inssong           #+#    #+#             */
/*   Updated: 2020/10/09 20:27:51 by inssong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnstr(const char *h, const char *n, size_t len)
{
	size_t	i;
	size_t	j;

	if (*n == '\0')
		return ((char*)h);
	i = 0;
	while (*(h + i))
	{
		if (*(h + i) == *n)
		{
			j = 0;
			while (*(n + j))
			{
				if (*(h + i + j) != *(n + j))
					break ;
				j++;
			}
			if (i + j <= len && *(n + j) == '\0')
				return ((char*)(h + i));
		}
		i++;
	}
	return (NULL);
}
