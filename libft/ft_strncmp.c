/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 12:22:14 by kdvarako          #+#    #+#             */
/*   Updated: 2024/03/25 12:43:31 by kdvarako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	unsigned int	i;
	unsigned char	*s1;
	unsigned char	*s2;

	if (n == 0)
		return (0);
	i = 0;
	s1 = (unsigned char *) str1;
	s2 = (unsigned char *) str2;
	while (i < n && s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
	{
		i++;
	}
	if (i >= n)
		i--;
	return (s1[i] - s2[i]);
}
