/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set_remove.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 16:46:19 by kdvarako          #+#    #+#             */
/*   Updated: 2024/09/17 11:44:39 by kdvarako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
chaeck if there is already the key
return 1 - if was found & 0 - if not
*/
int	find_key_env(char *key, t_env **env)
{
	t_env	*node;

	node = *env;
	while (node)
	{
		if (ft_strcmp(node->key, key) == 0)
			return (1);
		node = node->next;
	}
	return (0);
}

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
			if (node->value != NULL)
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
