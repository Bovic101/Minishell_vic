/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:43:58 by kdvarako          #+#    #+#             */
/*   Updated: 2024/09/30 12:26:56 by kdvarako         ###   ########.fr       */
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
					|| (str[i] >= 0 && str[i] <= 9)))
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
				perror("unset not a valid identifier\n");
				//printf("export: `%s': not a valid identifier\n", arg->value);
				//err handler
			}
			arg = arg->next;
		}
	}
	//ft_env_sort_declare(*env);
	//ft_env_print(env);
	return (0);
}
