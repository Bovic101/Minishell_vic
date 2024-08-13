/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set_remove.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 16:46:19 by kdvarako          #+#    #+#             */
/*   Updated: 2024/08/12 10:34:48 by kdvarako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_value(char *key, t_env **env)
{
	t_env	*node;

	node = *env;
	while (node)
	{
		if (ft_strcmp(node->key, key) == 0)
			return (node->value);
		node = node->next;
	}
	return (NULL);
}

void	set_value(char *key, char *new_value, t_env **env)
{
	t_env	*node;

	node = *env;
	while (node)
	{
		if (ft_strcmp(node->key, key) == 0)
		{
			free(node->value);
			node->value = NULL;
			node->value = new_value;
			break ;
		}
		node = node->next;
	}
}

void	remove_node(char *key, t_env **env)
{
	t_env	*node;
	t_env	*prev;

	node = *env;
	prev = NULL;
	while (node)
	{
		if (ft_strcmp(node->key, key) == 0)
		{
			free(node->value);
			free(node->key);
			if (prev == NULL)
				*env = node->next;
			else
				prev->next = node->next;
			free(node);
			break ;
		}
		prev = node;
		node = node->next;
	}
}
