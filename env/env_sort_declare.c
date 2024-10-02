/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_sort_declare.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vodebunm <vodebunm@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 12:38:26 by kdvarako          #+#    #+#             */
/*   Updated: 2024/10/02 13:59:26 by vodebunm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_sort_env_print(t_env **env)
{
	t_env	*node;

	node = *env;
	while (node)
	{
		/*if (ft_strcmp(node->key, "_") != 0 \
			&& ft_strcmp(node->key, "_exit_code") != 0)*/
		if (ft_strcmp(node->key, "_") != 0)
		{
			printf("declare -x ");
			printf("%s", node->key);
			if (node->value != NULL)
				printf("=\"%s\"", node->value);
			printf("\n");
		}
		node = node->next;
	}
}

void	ft_copy_env(t_env *src, t_env **copy)
{
	t_env	*ptr;
	char	*key;
	char	*value;

	if (src == NULL)
		return ;
	ptr = src;
	while (ptr)
	{
		key = ft_strdup(ptr->key);
		value = ft_strdup(ptr->value);
		add_env(key, value, copy);
		ptr = ptr->next;
	}
}


void	ft_sort_env(t_env **env)
{
	t_env	*node;
	t_env	*prev;
	char	*tmp;

	if (env == NULL)
		return ;
	prev = *env;
	node = prev->next;
	while (prev)
	{
		node = prev->next;
		while (node)
		{
			if (ft_strcmp(prev->key, node->key) > 0)
			{
				tmp = ft_strdup(prev->key);
				prev->key = ft_strdup(node->key);
				node->key = tmp;
				tmp = ft_strdup(prev->value);
				prev->value = ft_strdup(node->value);
				node->value = tmp;
			}
			node = node->next;
		}
		prev = prev->next;
	}
}

void	ft_env_sort_declare(t_env *env)
{
	t_env	*sort_env;

	sort_env = NULL;
	ft_copy_env(env, &sort_env);
	ft_sort_env(&sort_env);
	ft_sort_env_print(&sort_env);
	ft_free_env(&sort_env);
}
