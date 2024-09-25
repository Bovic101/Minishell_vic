/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 12:41:29 by kdvarako          #+#    #+#             */
/*   Updated: 2024/09/20 17:09:34 by kdvarako         ###   ########.fr       */
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
	!add if cmd == NULL
	*/
	if (if_builtin(node->cmd) == 0)
		execute_builtin(node, env);
	else
		executor_func(node, env);

	/*Here examples: 
	ls -l | grep mini | wc -l
	env | wc -l
	*/
}
void	pipe_util(t_parc *node)
{
	int	fd[2];
	int	err;

	err = pipe(fd);
	if (err < 0)
		return ;  //change to err handling
	node->fd_0 = fd[0];
	node->fd_1 = fd[1];
}

void	create_pipes(t_parc **parc)
{
	t_parc	*node;

	node = *parc;
	while (node != NULL)
	{
		pipe_util(node);
		node = node->next;
	}
}

void	close_fds(t_parc **parc)
{
	t_parc	*node;

	node = *parc;
	while (node != NULL)
	{
		close(node->fd_0);
		close(node->fd_1);
		node = node->next;
	}
}

int	execute_proces(t_parc **parc, t_env **env, int ncount)
{
	t_parc	*node;
	t_parc	*prev;
	int		pid;
	int		i;

	node = *parc;
	prev = NULL;
	i = 0;
	create_pipes(parc);
	while (i < ncount)
	{
		pid = fork();
		if (pid < 0)
			return (1); //err handling
		if (pid == 0)
		{
			if (i == 0)
			{
				dup2(node->fd_1, 1);
				close_fds(parc);
				ft_execute(node, env);
				return (0);
			}
			else if (i == ncount - 1)
			{
				dup2(prev->fd_0, 0);
				close_fds(parc);
				ft_execute(node, env);
				return (0);
			}
			else
			{
				dup2(prev->fd_0, 0);
				dup2(node->fd_1, 1);
				close_fds(parc);
				ft_execute(node, env);
				return (0);
			}
		}
		prev = node;
		node = node->next;
		i++;
	}
	// parent
	close_fds(parc);
	waitpid(pid, NULL, 0);
	return (0);
}


int	main_pipe_proc(t_parc **parc, t_env **env)
{
	pid_t	c_pid;
	int		status;
	int		fd0_before;
	int		fd1_before;
	// check if cmd exist -> if cmd not found - > err
	int ncount = ft_size_parc(*parc);
	if (ncount == 1)
	{
		if (if_builtin((*parc)->cmd) == 0)
		{
			fd0_before = dup(0);
			fd1_before = dup(1);
			ft_redirections(parc);
			execute_builtin(*parc, env);
			dup2(fd0_before, 0);
			dup2(fd1_before, 1);
		}
		else
		{
			c_pid = fork();
			if (c_pid == 0)
			{
				ft_redirections(parc);
				executor_func(*parc, env);
				exit(0);
			}
			else if (c_pid > 0)
			{
				waitpid(c_pid, &status, 0);
			}
			else
			{
				perror("Forking failed");
			}
		}
	}
	else
	{
		c_pid = fork();
		if (c_pid == 0)
		{
			//ft_redirections(parc);
			redirections_in(parc);
			//redirections_out(parc);
			execute_proces(parc, env, ncount);
			exit(0);
		}
		else if (c_pid > 0)
		{
			waitpid(c_pid, &status, 0);
		}
		else
		{
			perror("Forking failed");
		}
	}
	return (0);
}

/* prev copy
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
*/