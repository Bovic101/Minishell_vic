/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 11:29:41 by kdvarako          #+#    #+#             */
/*   Updated: 2024/08/15 12:05:46 by kdvarako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exe_pwd(t_parc *node, t_env **env)
{
	if (node->redirs == NULL)
		printf("%s\n", get_value("PWD", env));
}

void	exe_export(t_parc *node, t_env **env)
{
	if (node->args == NULL && node->redirs == NULL)
		ft_env_sort_declare(*env);
}

void	exe_env(t_parc *node, t_env **env)
{
	if (node->redirs == NULL)
	{
		ft_env_print(env);
		set_value("_", ft_strdup("env"), env);
	}
}

void	execute(t_parc **parc, t_env **env)
{
	t_parc	*node;

	node = *parc;
	while (node != NULL)
	{
		if (ft_strcmp(node->cmd, "pwd") == 0)
			exe_pwd(node, env);
		else if (ft_strcmp(node->cmd, "export") == 0)
			exe_export(node, env);
		else if (ft_strcmp(node->cmd, "env") == 0)
			exe_env(node, env);
		node = node->next;
	}
}
