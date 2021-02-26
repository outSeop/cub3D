/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inssong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 21:43:22 by inssong           #+#    #+#             */
/*   Updated: 2020/10/31 20:51:53 by inssong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	int		temp;

	i = 0;
	while (i < n)
	{
		if (!(*(s1 + i)) && *(s2 + i))
			return (-1);
		if (!(*(s2 + i)) && *(s1 + i))
			return (1);
		if (!(*(s1 + i)) && !(*(s2 + i)))
			break ;
		temp = *((unsigned char*)(s1 + i)) - (*((unsigned char*)(s2 + i)));
		if (temp != 0)
			return (temp);
		i++;
	}
	return (0);
}
