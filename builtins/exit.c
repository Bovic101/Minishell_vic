/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vodebunm <vodebunm@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:27:47 by kdvarako          #+#    #+#             */
/*   Updated: 2024/10/08 03:05:38 by vodebunm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	if_arg_num(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	while (arg[i] != '\0')
	{
		if (arg[i] >= '0' && arg[i] <= '9')
			i++;
		else
			return (1);
	}
	if (ft_atoi(arg) == 0 && ft_strlen(arg) > 2)
		return (1);
	return (0);
}

int	non_numeric_exit(char *cmd, char *value)
{
	print_error_msg(cmd, value, "numeric argument required");
	return (255);
}

int	exe_exit(t_parc *node, t_env **env)
{
	t_arg	*arg;
	int		exit_code;

	arg = node->args;
	exit_code = 0;
	if (arg == NULL)
		exit_code = *env[0]->exit_status;
	else if (if_arg_num(arg->value) == 0)
	{
		if (arg->next == NULL)
			exit_code = ft_atoi(arg->value);
		else
		{
			print_error_msg(node->cmd, NULL, "too many arguments");
			*env[0]->exit_status = 1;
			return (1);
		}
	}
	else
		exit_code = non_numeric_exit(node->cmd, arg->value);
	freeall(env, &node);
	exit(exit_code);
}
