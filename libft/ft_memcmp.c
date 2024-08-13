/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 11:55:55 by kdvarako          #+#    #+#             */
/*   Updated: 2024/03/25 12:09:51 by kdvarako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *str1, const void *str2, size_t n)
{
	unsigned char	*s1;
	unsigned char	*s2;
	unsigned int	i;

	if (n == 0)
		return (0);
	i = 0;
	s1 = (unsigned char *) str1;
	s2 = (unsigned char *) str2;
	while (i < (n - 1) && s1[i] == s2[i])
	{
		i++;
	}
	return (s1[i] - s2[i]);
}
