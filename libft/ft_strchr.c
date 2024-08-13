/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 12:12:36 by kdvarako          #+#    #+#             */
/*   Updated: 2024/03/25 12:20:40 by kdvarako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	const char		*res;
	unsigned int	i;
	unsigned int	len;

	i = 0;
	len = ft_strlen(str) + 1;
	res = NULL;
	while (i < len)
	{
		if (str[i] == (char)c)
		{
			res = &str[i];
			break ;
		}
		i++;
	}
	return ((char *)res);
}
