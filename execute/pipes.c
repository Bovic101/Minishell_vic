/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 12:41:29 by kdvarako          #+#    #+#             */
/*   Updated: 2024/09/16 16:19:11 by kdvarako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* 
 * Function to create pipes between child proces
 */

void	ft_execute(t_parc *node, t_env **env)
{
	/*
	check if from PATH or from builtins -> execute
	*/
	if (if_builtin(node->cmd) == 0)
		execute_builtin(node, env);
	else
		executor_func(node, env);

	/*Here just example: 
	ls -l | grep mini | wc -l
	*//*
	if (ft_strcmp(parc->cmd, "ls") == 0)
		execlp("ls", "ls", "-l", (char *) NULL);
	else if (ft_strcmp(parc->cmd, "grep") == 0)
		execlp("grep", "grep", "mini", (char *) NULL);
	else if (ft_strcmp(parc->cmd, "wc") == 0)
		execlp("wc", "wc", "-l", (char *) NULL);
		*/
}

int	execute_proces(t_parc **parc, t_env **env, int ncount)
{
	t_parc	*node;
	int		pid[ncount];
	int		fd[ncount - 1][2];

	for (int i = 0; i < ncount - 1; i++)
	{
		if (pipe(fd[i]) < 0)
			return (1);
	}
	node = *parc;
	for (int i = 0; i < ncount; i++)
	{
		pid[i] = fork();
		if (pid[i] < 0)
			return (1);
		if (pid[i] == 0)
		{
			if (i == 0)
			{
				for (int j = 0; j < ncount - 1; j++)
				{
					if (j == 0)
						close(fd[j][0]);
					else
					{
						close(fd[j][0]);
						close(fd[j][1]);
					}
				}
				dup2(fd[0][1], 1);
				close(fd[0][1]);
				ft_execute(node, env);
				return (0);
			}
			else if (i == ncount - 1)
			{
				for (int j = 0; j < ncount - 1; j++)
				{
					if (j == ncount - 2)
						close(fd[j][1]);
					else
					{
						close(fd[j][0]);
						close(fd[j][1]);
					}
				}
				dup2(fd[ncount - 2][0], 0);
				close(fd[ncount - 2][0]);
				ft_execute(node, env);
				return (0);
			}
			else
			{
				for (int j = 0; j < ncount - 1; j++)
				{
					if (j == i - 1)
						close(fd[j][1]);
					else if (j == i)
						close(fd[j][0]);
					else
					{
						close(fd[j][0]);
						close(fd[j][1]);
					}
				}
				dup2(fd[i - 1][0], 0);
				dup2(fd[i][1], 1);
				close(fd[i - 1][0]);
				close(fd[i][1]);
				ft_execute(node, env);
				return (0);
			}
		}
		node = node->next;
	}
	// parent
	for (int i = 0; i < ncount - 1; i++)
	{
		close(fd[i][0]);
		close(fd[i][1]);
	}
	for (int i = 0; i < ncount; i++)
	{
		waitpid(pid[i], NULL, 0);
	}
	return (0);
}

int	main_pipe_proc(t_parc **parc, t_env **env)
{
	// check if cmd exist -> if cmd not found - > err
	int ncount = ft_size_parc(*parc);
	if (ncount == 1)
	{
		if (if_builtin((*parc)->cmd) == 0)
			execute_builtin(*parc, env);
		else
			executor_func(*parc, env);
	}
	else
		execute_proces(parc, env, ncount);
	return (0);
}
