/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 12:23:38 by kdvarako          #+#    #+#             */
/*   Updated: 2024/03/25 12:32:51 by kdvarako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	const char		*res;
	unsigned int	i;
	unsigned int	len;

	i = 0;
	res = NULL;
	len = ft_strlen(str) + 1;
	while (i < len)
	{
		if (str[i] == (unsigned char)c)
		{
			res = &str[i];
		}
		i++;
	}
	return ((char *) res);
}
