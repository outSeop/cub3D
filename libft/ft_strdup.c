/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inssong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 20:06:16 by inssong           #+#    #+#             */
/*   Updated: 2020/10/31 19:34:16 by inssong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strdup(const char *s1)
{
	size_t	size;
	char	*s2;

	size = 0;
	while (*(s1 + size++))
		;
	if (!(s2 = (char *)malloc(sizeof(char) * size)))
		return (NULL);
	size--;
	*(s2 + size) = '\0';
	while (size--)
		*(s2 + size) = *(s1 + size);
	return (s2);
}
