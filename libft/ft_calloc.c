/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inssong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 19:45:58 by inssong           #+#    #+#             */
/*   Updated: 2020/10/31 19:35:28 by inssong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_calloc(size_t count, size_t size)
{
	size_t	i;
	char	*res;

	if (!(res = (char *)malloc(size * count)))
		return (NULL);
	i = 0;
	while (i < size * count)
	{
		res[i] = 0;
		i++;
	}
	return (res);
}
