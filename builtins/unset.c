/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:43:58 by kdvarako          #+#    #+#             */
/*   Updated: 2024/10/05 11:15:38 by kdvarako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	right_varname_u(char *str)
{
	int	i;

	i = 1;

	if (str[0] == '_' || (str[0] >= 'a' && str[0] <= 'z') \
		|| (str[0] >= 'A' && str[0] <= 'Z'))
	{
		while (str[i] != '\0')
		{
			if (!(str[i] == '_' || (str[i] >= 'a' && str[i] <= 'z') || \
				(str[i] >= 'A' && str[i] <= 'Z') \
					|| (str[i] >= '0' && str[i] <= '9')))
				return (1);
			i++;
		}
	}
	else
		return (1);
	return (0);
}

int	exe_unset(t_parc *node, t_env **env)
{
	t_arg	*arg;
	int		return_status;

	return_status = 0;
	if (node->args != NULL)
	{
		arg = node->args;
		while (arg != NULL)
		{
			if (right_varname_u(arg->value) == 0)
			{
				remove_node(arg->value, env);
			}
			else
			{
				print_error_msg(node->cmd, arg->value, \
					"not a valid identifier");
				return_status = 1;
			}
			arg = arg->next;
		}
	}
	return (return_status);
}
