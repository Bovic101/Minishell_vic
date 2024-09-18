/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:44:06 by kdvarako          #+#    #+#             */
/*   Updated: 2024/09/18 15:45:16 by kdvarako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exe_cd(t_parc *node, t_env **env)
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
		//printf("pwd buf: %s\n", getcwd(buf, sizeof(buf)));
		//printf("pwd before: %s\n", get_value("PWD", env));
		set_value("PWD", getcwd(buf, sizeof(buf)), env);  //allocate? what return getcwd - err?
		//printf("pwd after: %s\n", get_value("PWD", env));
		//printf("old after: %s\n", get_value("OLDPWD", env));
		set_value("OLDPWD", cur_pwd, env);
		//printf("old after: %s\n", get_value("OLDPWD", env));
	}
	else
		return ; //err hanling (file not found,..)
}
