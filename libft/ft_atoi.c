/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 11:29:57 by kdvarako          #+#    #+#             */
/*   Updated: 2024/03/27 11:50:36 by kdvarako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

static int	ft_getnum(const char *str, int sym);
static int	ft_findfirst(const char *str);

int	ft_atoi(const char *str)
{
	int			i;
	int			sym;
	int			num;
	const char	*ptr;

	sym = 1;
	if (ft_strlen(str) < 1)
		return (0);
	i = ft_findfirst(str);
	if (str[i] == '+')
	{
		sym = 1;
		i++;
	}
	else if (str[i] == '-')
	{
		sym = -1;
		i++;
	}
	ptr = &str[i];
	num = ft_getnum(ptr, sym);
	return (num * sym);
}

static int	ft_getnum(const char *str, int sym)
{
	int		i;
	long	num;

	i = 0;
	num = 0;
	while (str[i] >= '0' && str[i] <= '9' && str[i] != '\0')
	{
		num = num * 10;
		num = num + str[i] - 48;
		i++;
	}
	if ((num * sym) < INT_MIN || (num * sym) > INT_MAX)
		num = 0;
	return (num);
}

static int	ft_findfirst(const char *str)
{
	int	i;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	return (i);
}
