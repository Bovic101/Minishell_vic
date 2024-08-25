/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_libft.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vodebunm <vodebunm@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 20:17:41 by vodebunm          #+#    #+#             */
/*   Updated: 2024/08/25 20:38:07 by vodebunm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strcpy(char *dest, const char *src)
{
	int i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return(dest);
}

char *ft_strcat(char *dest, const char *src)
{
   // Find the end of the destination string
    char *dest_end;

    dest_end = dest;
    while (*dest_end != '\0')
	{
        dest_end++;
    }
    while (*src != '\0')
	{
		*dest_end = *src;
        dest_end++;
        src++;
    }

    *dest_end = '\0';

    return(dest);
}

