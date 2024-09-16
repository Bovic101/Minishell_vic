/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 11:29:41 by kdvarako          #+#    #+#             */
/*   Updated: 2024/09/16 11:32:39 by kdvarako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exe_echo(t_parc *node, t_env **env)
{
	if (node->redirs_in == NULL && node->redirs_out == NULL)
	{
		ft_putstr_fd("echo\n", 1);
	}
}

void	exe_cd(t_parc *node, t_env **env)
{
	if (node->redirs_in == NULL && node->redirs_out == NULL)
	{
		ft_putstr_fd("cd\n", 1);
	}
}

void	exe_pwd(t_parc *node, t_env **env)
{
	if (node->redirs_in == NULL && node->redirs_out == NULL)
		printf("%s\n", get_value("PWD", env));
}

void	exe_export(t_parc *node, t_env **env)
{
	if (node->args == NULL && node->redirs_in == NULL \
		&& node->redirs_out == NULL)
		ft_env_sort_declare(*env);
}

void	exe_unset(t_parc *node, t_env **env)
{
	/*if (node->args == NULL && node->redirs_in == NULL \
		&& node->redirs_out == NULL)
		*/
		ft_putstr_fd("unset\n", 1);
}

void	exe_env(t_parc *node, t_env **env)
{
	if (node->redirs_in == NULL && node->redirs_out == NULL)
	{
		ft_env_print(env);
		set_value("_", ft_strdup("env"), env);
	}
}

int	if_builtin(char *cmd)
{
	/*
	function returns 0 if cmd is one of builtin
	*/
	if (ft_strcmp(node->cmd, "echo") == 0)
		return (0);
	if (ft_strcmp(node->cmd, "cd") == 0)
		return (0);
	if (ft_strcmp(node->cmd, "pwd") == 0)
		return (0);
	if (ft_strcmp(node->cmd, "export") == 0)
		return (0);
	if (ft_strcmp(node->cmd, "unset") == 0)
		return (0);
	if (ft_strcmp(node->cmd, "env") == 0)
		return (0);
	//if (ft_strcmp(node->cmd, "exit") == 0)
		//return (0);
	return (1);
}

void	execute_builtin(t_parc *node, t_env **env)
{
	if (ft_strcmp(node->cmd, "echo") == 0)
		exe_echo(node, env);
	else if (ft_strcmp(node->cmd, "cd") == 0)
		exe_cd(node, env);
	else if (ft_strcmp(node->cmd, "pwd") == 0)
		exe_pwd(node, env);
	else if (ft_strcmp(node->cmd, "export") == 0)
		exe_export(node, env);
	else if (ft_strcmp(node->cmd, "unset") == 0)
		exe_unset(node, env);
	else if (ft_strcmp(node->cmd, "env") == 0)
		exe_env(node, env);
	//else if (ft_strcmp(node->cmd, "exit") == 0)
		//exe_exit(node, env);
}
