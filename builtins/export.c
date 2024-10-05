/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:44:01 by kdvarako          #+#    #+#             */
/*   Updated: 2024/10/05 11:34:49 by kdvarako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	right_varname_e(char *str)
{
	int	i;

	i = 1;

	if (str[0] == '_' || (str[0] >= 'a' && str[0] <= 'z') || \
		(str[0] >= 'A' && str[0] <= 'Z'))
	{
		while (str[i] != '\0' && str[i] != '=')
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

void	set_variable(t_arg *arg, int len, t_env **env)
{
	int	fl;

	fl = 0;
	while (arg->value[len] != '\0')
	{
		if (arg->value[len] == '=')
		{
			fl = 1;
			break ;
		}
		len++;
	}
	if (fl == 1)
		add_set_env(ft_strndup(arg->value, len), \
			ft_strdup(&arg->value[len + 1]), env);
	else
		add_set_env(ft_strndup(arg->value, len), NULL, env);
}

int	exe_export(t_parc *node, t_env **env)
{
	t_arg	*arg;
	int		len;
	int		return_status;

	return_status = 0;
	if (node->args == NULL)
		ft_env_sort_declare(*env);
	else
	{
		arg = node->args;
		while (arg != NULL)
		{
			len = 0;
			if (right_varname_e(arg->value) == 0)
				set_variable(arg, len, env);
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
