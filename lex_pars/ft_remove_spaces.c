/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_spaces.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vodebunm <vodebunm@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 16:01:08 by kdvarako          #+#    #+#             */
/*   Updated: 2024/10/08 20:37:18 by vodebunm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	new_str(char *new, char **tmp, int i)
{
	int	j;

	j = 0;
	while (tmp[j] != NULL)
	{
		if (new == NULL)
			new = ft_strjoin(tmp[j], " ");
		else if (j < (i - 1))
			new = ft_strjoin(ft_strjoin(new, tmp[j]), " ");
		else
			new = ft_strjoin(new, tmp[j]);
		j++;
	}
}

void	free_tmp(char **tmp)
{
	int	i;

	i = 0;
	while (tmp[i] != NULL)
	{
		free(tmp[i]);
		i++;
	}
	free(tmp);
}
/*
char	*ft_remove_spaces(char *value)
{
	char	**tmp;
	int		i;
	char	*new;

	i = 0;
	new = NULL;
	tmp = ft_split(value, ' ');
	if (tmp == NULL)
		return (value);
	while (tmp[i] != NULL)
		i++;
	if (i > 1)
	{
		new_str(new, tmp, i);
	}
	else
	{
		free_tmp(tmp);
		return (value);
	}
	free_tmp(tmp);
	return (free(value), new);
}*/
