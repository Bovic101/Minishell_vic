/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:43:58 by kdvarako          #+#    #+#             */
/*   Updated: 2024/09/18 15:46:45 by kdvarako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exe_unset(t_parc *node, t_env **env)
{
	t_arg	*arg;
	/*if (node->args == NULL && node->redirs_in == NULL \
		&& node->redirs_out == NULL)
		*/
	if (node->args != NULL)
	{
		arg = node->args;
		while (arg != NULL)
		{
			remove_node(arg->value, env);
			arg = arg->next;
		}
	}
	//ft_env_sort_declare(*env);
	//ft_env_print(env);
}
