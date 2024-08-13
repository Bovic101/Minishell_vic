/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:28:37 by kdvarako          #+#    #+#             */
/*   Updated: 2024/03/27 11:54:55 by kdvarako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putposnum(long n, int fd);

void	ft_putnbr_fd(int n, int fd)
{
	long	l;

	if (n == 0)
		ft_putchar_fd('0', fd);
	else
	{
		l = n;
		if (l < 0)
		{
			ft_putchar_fd('-', fd);
			l = -l;
		}
		ft_putposnum(l, fd);
	}
}

static void	ft_putposnum(long n, int fd)
{
	long	i;

	i = 1;
	while (n / i > 0)
		i = i * 10;
	i = i / 10;
	while (i > 0)
	{
		ft_putchar_fd((n / i + '0'), fd);
		n = n - n / i * i;
		i = i / 10;
	}
}
