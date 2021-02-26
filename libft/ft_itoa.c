/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inssong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 19:23:24 by inssong           #+#    #+#             */
/*   Updated: 2020/11/16 21:16:53 by inssong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				get_len(long long tmp)
{
	if (tmp < 10)
		return (1);
	return (get_len(tmp / 10) + 1);
}

char			*ft_itoa(int n)
{
	long long	tmp;
	int			len;
	char		*res;

	len = 0;
	tmp = n;
	if (n < 0)
	{
		len++;
		tmp = -tmp;
	}
	len += get_len(tmp);
	if (!(res = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	res[len] = '\0';
	res[--len] = tmp % 10 + '0';
	while (tmp /= 10)
		res[--len] = tmp % 10 + '0';
	if (n < 0)
		res[0] = '-';
	return (res);
}
