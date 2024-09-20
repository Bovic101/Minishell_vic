/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 11:29:41 by kdvarako          #+#    #+#             */
/*   Updated: 2024/09/20 13:02:01 by kdvarako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	if_builtin(char *cmd)
{
	/*
	function returns 0 if cmd is one of builtin
	*/
	if (ft_strcmp(cmd, "echo") == 0)
		return (0);
	if (ft_strcmp(cmd, "cd") == 0)
		return (0);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (0);
	if (ft_strcmp(cmd, "export") == 0)
		return (0);
	if (ft_strcmp(cmd, "unset") == 0)
		return (0);
	if (ft_strcmp(cmd, "env") == 0)
		return (0);
	//if (ft_strcmp(cmd, "exit") == 0)
		//return (0);
	return (1);
}

int	execute_builtin(t_parc *node, t_env **env)
{
	if (ft_strcmp(node->cmd, "echo") == 0)
		exe_echo(node);
	else if (ft_strcmp(node->cmd, "cd") == 0)
		exe_cd(node, env);
	else if (ft_strcmp(node->cmd, "pwd") == 0)
		exe_pwd(env);
	else if (ft_strcmp(node->cmd, "export") == 0)
		exe_export(node, env);
	else if (ft_strcmp(node->cmd, "unset") == 0)
		exe_unset(node, env);
	else if (ft_strcmp(node->cmd, "env") == 0)
		exe_env(env);
	//else if (ft_strcmp(node->cmd, "exit") == 0)
		//exe_exit(node, env);
		return (0);
}
