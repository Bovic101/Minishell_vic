/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 11:54:25 by kdvarako          #+#    #+#             */
/*   Updated: 2024/03/27 11:52:54 by kdvarako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	ft_numberscount(long n);
static long	ft_ten(long num);
static char	*ft_createstr(long l, long count, char *str);

char	*ft_itoa(int n)
{
	long	count;
	char	*str;
	long	l;

	l = n;
	count = ft_numberscount(l);
	str = (char *)malloc(count + 1);
	if (!str)
		return (NULL);
	str = ft_createstr(l, count, str);
	return (str);
}

static long	ft_numberscount(long n)
{
	long	count;

	count = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n = -n;
		count++;
	}
	while (n != 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

static long	ft_ten(long num)
{
	long	i;

	i = 1;
	num--;
	while (num > 0)
	{
		i = i * 10;
		num --;
	}
	return (i);
}

static char	*ft_createstr(long l, long count, char *str)
{
	int	i;

	i = 0;
	if (l < 0)
	{
		str[i] = '-';
		l = -l;
		i++;
		count--;
	}
	while (count > 0)
	{
		str[i] = l / ft_ten(count) + '0';
		l = l - l / ft_ten(count) * ft_ten(count);
		count--;
		i++;
	}
	str[i] = '\0';
	return (str);
}
