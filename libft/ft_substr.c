/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:30:51 by kdvarako          #+#    #+#             */
/*   Updated: 2024/03/25 12:35:23 by kdvarako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*subs;
	unsigned int	i;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		len = 0;
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	subs = (char *)malloc(len + 1);
	if (!subs)
		return (NULL);
	i = 0;
	while (i < len && s[start] != '\0')
	{
		subs[i] = s[start];
		i++;
		start++;
	}
	subs[i] = '\0';
	return (subs);
}
