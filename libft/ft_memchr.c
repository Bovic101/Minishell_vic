/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 11:54:57 by kdvarako          #+#    #+#             */
/*   Updated: 2024/03/25 12:08:43 by kdvarako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	const char		*res;
	const char		*s;
	unsigned int	i;

	i = 0;
	res = NULL;
	s = (char *) str;
	while (i < n)
	{
		if ((unsigned char) s[i] == (unsigned char) c)
		{
			res = &s[i];
			break ;
		}
		i++;
	}
	return ((void *)res);
}
