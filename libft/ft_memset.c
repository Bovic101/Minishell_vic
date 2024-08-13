/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 12:07:51 by kdvarako          #+#    #+#             */
/*   Updated: 2024/03/25 12:13:06 by kdvarako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	size_t			i;
	unsigned char	ch;
	unsigned char	*p;

	i = 0;
	ch = c - 48 + '0';
	p = (unsigned char *) str;
	while (i < n)
	{
		*p = ch;
		p++;
		i++;
	}
	return (str);
}
