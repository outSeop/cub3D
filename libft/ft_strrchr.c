/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inssong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 16:51:23 by inssong           #+#    #+#             */
/*   Updated: 2020/10/31 13:58:11 by inssong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strrchr(const char *s, int c)
{
	char	*temp;

	temp = (char*)s;
	while (*temp++)
		;
	temp--;
	while ((char*)s <= temp)
	{
		if (*temp == (char)c)
			return (temp);
		temp--;
	}
	return (NULL);
}
