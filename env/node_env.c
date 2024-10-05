/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 12:11:32 by kdvarako          #+#    #+#             */
/*   Updated: 2024/10/05 18:04:36 by kdvarako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*ft_env_new(char *key, char *value)
{
	t_env	*a;

	a = malloc(sizeof(t_env));
	if (a == NULL)
		return (NULL);
	a->value = value;
	a->key = key;
	a->next = NULL;
	return (a);
}

t_env	*ft_env_last(t_env *a)
{
	t_env	*ptr;

	if (a == NULL)
		return (NULL);
	ptr = a;
	while (ptr->next != NULL)
	{
		ptr = ptr->next;
	}
	return (ptr);
}

void	ft_env_add_back(t_env **lst, t_env *new)
{
	t_env	*last;

	if (new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = ft_env_last(*lst);
	last->next = new;
}

void	ft_env_print(t_env **env)
{
	t_env	*node;

	node = *env;
	while (node)
	{
		if (node->value != 0)
		{
			printf("%s=", node->key);
			if (ft_strcmp(node->key, "_") == 0)
				printf("%s\n", "/usr/bin/env");
			else
				printf("%s\n", node->value);
		}
		node = node->next;
	}
}

void	ft_free_env(t_env	**env)
{
	t_env	*node;
	t_env	*tmp;

	if (!env)
		return ;
	tmp = *env;
	while (tmp)
	{
		free(tmp->key);
		free(tmp->value);
		node = tmp->next;
		free(tmp);
		tmp = node;
	}
	*env = NULL;
}
