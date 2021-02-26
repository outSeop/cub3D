/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inssong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 11:35:32 by inssong           #+#    #+#             */
/*   Updated: 2020/11/13 11:35:33 by inssong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	i;
	size_t	s_len;
	size_t	res_len;

	res = NULL;
	res_len = 1;
	s_len = ft_strlen(s);
	if (s_len >= start)
	{
		res_len = s_len - start + 1;
		res_len = res_len > len ? len + 1 : res_len;
	}
	else
		start = s_len;
	if (!(res = (char *)malloc(sizeof(char) * res_len)))
		return (NULL);
	i = 0;
	while (i < len && *(s + start + i))
	{
		*(res + i) = *(s + start + i);
		i++;
	}
	*(res + i) = '\0';
	return (res);
}
