/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:44:01 by kdvarako          #+#    #+#             */
/*   Updated: 2024/09/20 11:48:31 by kdvarako         ###   ########.fr       */
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
					|| (str[i] >= 0 && str[i] <= 9)))
				return (1);
			i++;
		}
	}
	else
		return (1);
	return (0);
}

void	exe_export(t_parc *node, t_env **env)
{
	t_arg	*arg;
	int		len;
	int		fl;

	if (node->args == NULL)
		ft_env_sort_declare(*env);
	else
	{
		arg = node->args;
		while (arg != NULL)
		{
			len = 0;
			fl = 0;
			if (right_varname_e(arg->value) == 0)
			{
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
			}
			else
			{
				perror("export not a valid identifier\n");
				//printf("export: `%s': not a valid identifier\n", arg->value);
				//err handler
			}
			arg = arg->next;
		}
		//ft_env_sort_declare(*env);
		//ft_env_print(env);
	}
}
