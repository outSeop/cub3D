/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inssong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 11:35:44 by inssong           #+#    #+#             */
/*   Updated: 2020/11/13 11:35:45 by inssong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			find_set(char c, char const *set)
{
	size_t	i;
	size_t	exist;

	i = 0;
	exist = 0;
	while (*(set + i))
	{
		if (*(set + i) == c)
			exist = 1;
		i++;
	}
	return (exist);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	finish;
	char	*res;

	start = 0;
	finish = ft_strlen(s1) - 1;
	res = NULL;
	while (find_set(*(s1 + start), set))
		start++;
	if (!(*(s1 + start)))
	{
		if (!(res = (char *)malloc(sizeof(char))))
			return (NULL);
		*res = '\0';
		return (res);
	}
	while (find_set(*(s1 + finish), set))
		finish--;
	if (!(res = (char *)malloc(sizeof(char) * (finish - start) + 2)))
		return (NULL);
	ft_strlcpy(res, s1 + start, finish - start + 2);
	return (res);
}
