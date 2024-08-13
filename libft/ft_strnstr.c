/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 12:23:05 by kdvarako          #+#    #+#             */
/*   Updated: 2024/03/27 11:56:43 by kdvarako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_findstr(const char *s1, const char *s2, size_t n);

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	char	*ptr;

	if (ft_strlen(s2) == 0)
		return ((char *) s1);
	ptr = ft_findstr(s1, s2, n);
	return (ptr);
}

static char	*ft_findstr(const char *s1, const char *s2, size_t n)
{
	size_t		i;
	size_t		j;
	size_t		k;

	i = 0;
	while (i < n && s1[i] != '\0')
	{
		j = 0;
		k = i;
		while (i < n && s1[i] == s2[j])
		{
			i++;
			j++;
			if (!s2[j])
				return ((char *) &s1[k]);
			if (!s1[i])
				break ;
		}
		i = k;
		i++;
	}
	return (NULL);
}
