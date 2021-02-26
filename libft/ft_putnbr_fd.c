/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inssong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 11:38:54 by inssong           #+#    #+#             */
/*   Updated: 2020/11/16 19:17:49 by inssong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				ft_putnbr_fd(int n, int fd)
{
	long long		ten;
	long long		tmp;
	char			ch;

	if (n == 0)
		write(fd, &"0", 1);
	tmp = n;
	ten = 1;
	if (n < 0)
	{
		write(fd, &"-", 1);
		tmp *= -1;
	}
	while (tmp / ten > 0)
		ten *= 10;
	ten /= 10;
	while (ten)
	{
		ch = tmp / ten + '0';
		write(fd, &ch, 1);
		tmp %= ten;
		ten /= 10;
	}
}
