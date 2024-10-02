/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:27:47 by kdvarako          #+#    #+#             */
/*   Updated: 2024/10/02 18:29:51 by kdvarako         ###   ########.fr       */
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

int	exe_exit(t_parc *node, t_env **env)
{
	t_arg	*arg;

	arg = node->args;
	if (arg == NULL)
		exit (*env[0]->exit_status);
	printf("exit\n");
	if (if_arg_num(arg->value) == 0)
	{
		if (arg->next == NULL)
			exit (ft_atoi(arg->value));
		else
		{
			print_error_msg(node->cmd, NULL, "too many arguments");
			exit (1);
		}
	}
	else
	{
		print_error_msg(node->cmd, arg->value, "numeric argument required");
		exit (255);
	}
	exit (*env[0]->exit_status);
}
