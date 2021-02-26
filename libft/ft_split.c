/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inssong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 11:35:18 by inssong           #+#    #+#             */
/*   Updated: 2020/11/19 20:56:24 by inssong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		count_c(char const *s, char c)
{
	size_t	num;
	size_t	i;

	num = 0;
	i = 0;
	while (*(s + i))
	{
		if (i == 0)
		{
			if (*(s + i) != c)
				num++;
		}
		else
		{
			if (*(s + i - 1) == c && *(s + i))
				num++;
		}
		i++;
	}
	return (num);
}

char		**free_fail(char **s, int i)
{
	while (i > 0)
		free(s[i--]);
	free(s);
	return (NULL);
}

char		**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	start;
	size_t	idx;
	char	**res;

	res = NULL;
	if (!(res = (char **)malloc(sizeof(char*) * (count_c(s, c) + 1))))
		return (NULL);
	idx = 0;
	i = 0;
	while (*(s + i))
		if (*(s + i) != c)
		{
			start = i;
			while (*(s + i) && *(s + i) != c)
				i++;
			if (!(res[idx] = (char *)malloc(sizeof(char) * (i - start) + 1)))
				return (free_fail(res, idx));
			ft_strlcpy(res[idx++], s + start, i - start + 1);
		}
		else
			i++;
	res[idx] = NULL;
	return (res);
}
