/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:30:08 by kdvarako          #+#    #+#             */
/*   Updated: 2024/03/27 11:39:22 by kdvarako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_startstr(char const *s1, char const *set);
static int	ft_endstr(char const *s1, const char *set);

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*s;
	int		start;
	int		end;
	int		i;

	if (!s1 || !set)
		return (NULL);
	start = ft_startstr(s1, set);
	end = ft_endstr(s1, set);
	if (end <= start)
		i = 0;
	else
		i = end - start + 1;
	s = (char *)malloc(sizeof(char) * (i + 1));
	if (!s)
		return (NULL);
	i = 0;
	while (start <= end && s1[start] != '\0')
	{
		s[i] = s1[start];
		i++;
		start++;
	}
	s[i] = '\0';
	return (s);
}

static int	ft_startstr(char const *s1, char const *set)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (s1[i] != '\0')
	{
		j = 0;
		k = 0;
		while (set[j] != '\0')
		{
			if (set[j] == s1[i])
			{
				k = 1;
				break ;
			}
			j++;
		}
		if (k == 0)
			break ;
		i++;
	}
	return (i);
}

static int	ft_endstr(char const *s1, const char *set)
{
	int	i;
	int	j;
	int	k;

	i = ft_strlen(s1) - 1;
	k = 0;
	while (i >= 0)
	{
		j = 0;
		k = 0;
		while (set[j] != '\0')
		{
			if (set[j] == s1[i])
			{
				k = 1;
				break ;
			}
			j++;
		}
		if (k == 0)
			break ;
		i--;
	}
	return (i);
}
