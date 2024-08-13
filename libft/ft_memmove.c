/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 12:07:05 by kdvarako          #+#    #+#             */
/*   Updated: 2024/03/26 16:52:00 by kdvarako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*p_dest;
	const char	*p_src;

	if (dest == src)
		return (dest);
	if (dest < src)
	{
		return (ft_memcpy(dest, src, n));
	}
	else
	{
		p_dest = dest;
		p_src = src;
		while (n--)
		{
			p_dest[n] = p_src[n];
		}
	}
	return (dest);
}
