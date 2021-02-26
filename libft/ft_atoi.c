/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inssong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 22:04:44 by inssong           #+#    #+#             */
/*   Updated: 2020/11/09 04:14:41 by inssong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define LLONG_MAX 9223372036854775807

int						ft_atoi(const char *str)
{
	unsigned long long	res;
	int					sign;

	res = 0;
	sign = 1;
	while (*str == ' ' || (9 <= *str && *str <= 13))
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
	{
		str++;
		sign = -1;
	}
	while (*str && ('0' <= *str && *str <= '9'))
	{
		res = (res * 10) + (int)*str++ - '0';
		if (res > LLONG_MAX - 1 && sign == -1)
			return (0);
		if (res > LLONG_MAX && sign == 1)
			return (-1);
	}
	return (res * sign);
}
