/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inssong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 21:03:49 by inssong           #+#    #+#             */
/*   Updated: 2020/10/12 23:49:44 by inssong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;
	size_t	temp;

	i = 0;
	while (i < n)
	{
		temp = *((unsigned char*)s1 + i) - *((unsigned char*)s2 + i);
		if (temp != 0)
			return (temp);
		i++;
	}
	return (0);
}
