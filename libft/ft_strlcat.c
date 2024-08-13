/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 12:18:43 by kdvarako          #+#    #+#             */
/*   Updated: 2024/03/25 12:25:23 by kdvarako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t			i;
	size_t			j;
	char			*ptr;
	unsigned int	len;

	if (size < ft_strlen(dst) + 1)
		return (size + ft_strlen(src));
	len = ft_strlen(dst);
	ptr = dst;
	i = 0;
	while (dst[i] != '\0')
		i++;
	size = size - ft_strlen(dst) - 1;
	j = 0;
	while (size > 0 && src[j] != '\0')
	{
		dst[i] = src[j];
		i++;
		j++;
		size--;
	}
	dst = ptr;
	dst[i] = '\0';
	return (len + ft_strlen(src));
}
