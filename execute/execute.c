/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 11:29:41 by kdvarako          #+#    #+#             */
/*   Updated: 2024/09/30 15:30:35 by kdvarako         ###   ########.fr       */
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
	int	return_status;

	return_status = 0;
	if (ft_strcmp(node->cmd, "echo") == 0)
		return_status = exe_echo(node);
	else if (ft_strcmp(node->cmd, "cd") == 0)
		return_status = exe_cd(node, env);
	else if (ft_strcmp(node->cmd, "pwd") == 0)
		return_status = exe_pwd(env);
	else if (ft_strcmp(node->cmd, "export") == 0)
		return_status = exe_export(node, env);
	else if (ft_strcmp(node->cmd, "unset") == 0)
		return_status = exe_unset(node, env);
	else if (ft_strcmp(node->cmd, "env") == 0)
		return_status = exe_env(env);
	//else if (ft_strcmp(node->cmd, "exit") == 0)
		//exe_exit(node, env);
	if (return_status == 0)
		return (0);
	else
		return (1);
}

/*
	check if from PATH or from builtins or cmd == NULL -> execute
*/
int	ft_execute(t_parc *node, t_env **env)
{
	pid_t	c_pid;
	int		status;
	int		fd0_before;
	int		fd1_before;

	fd0_before = dup(0);
	fd1_before = dup(1);
	if (node->cmd == NULL)
	{
		status = ft_redirections(node);
	}
	else if (if_builtin(node->cmd) == 0)
	{
		status = ft_redirections(node);
		if (status == 0)
			status = execute_builtin(node, env);
	}
	else
	{
		status = ft_redirections(node);
		if (status == 0)
		{
			c_pid = fork();
			if (c_pid == 0)
			{
				executor_func(node, env);
				exit(0);
			}
			else if (c_pid > 0)
			{
				waitpid(c_pid, &status, 0);
			}
			else
			{
				//free before, exit?
				perror("Forking failed");
			}
		}
	}
	dup2(fd0_before, 0);
	dup2(fd1_before, 1);
	return (status);
}

/*Here examples: 
	ls -l | grep mini | wc -l
	env | wc -l
	pwd | echo "abc" klm "$PWD"
	*/
