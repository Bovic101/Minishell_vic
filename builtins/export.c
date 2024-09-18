/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:44:01 by kdvarako          #+#    #+#             */
/*   Updated: 2024/09/18 15:46:07 by kdvarako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exe_export(t_parc *node, t_env **env)
{
	t_arg	*arg;
	int		len;
	int		fl;

	/*if (node->args == NULL && node->redirs_in == NULL \
		&& node->redirs_out == NULL)*/
	if (node->args == NULL)
		ft_env_sort_declare(*env);
	else
	{
		arg = node->args;
		while (arg != NULL)
		{
			len = 0;
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
				add_set_env(ft_strndup(arg->value, len), ft_strdup(&arg->value[len + 1]), env);
			else
				add_set_env(ft_strndup(arg->value, len), NULL, env);
			arg = arg->next;
		}
		//ft_env_sort_declare(*env);
		//ft_env_print(env);
	}
}
