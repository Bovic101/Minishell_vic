/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vodebunm <vodebunm@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:44:06 by kdvarako          #+#    #+#             */
/*   Updated: 2024/10/08 03:04:55 by vodebunm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exe_cd(t_parc *node, t_env **env)
{
	char	*cur_pwd;
	char	buf[PATH_MAX];
	int		res;

	cur_pwd = get_value("PWD", env);
	if (node->args == NULL)
		res = chdir(get_value("HOME", env));
	else
		res = chdir(node->args->value);
	if (res == 0)
	{
		set_value("OLDPWD", ft_strdup(cur_pwd), env);
		set_value("PWD", ft_strdup(getcwd(buf, sizeof(buf))), env);
	}
	else
	{
		print_error_msg(node->cmd, node->args->value,
			"No such file or directory");
		return (res);
	}
	return (res);
}
