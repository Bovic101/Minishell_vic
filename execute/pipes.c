/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 12:41:29 by kdvarako          #+#    #+#             */
/*   Updated: 2024/09/30 17:57:33 by kdvarako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* 
 * Function to create pipes between child proces
 */

int	pipe_util(t_parc *node)
{
	int	fd[2];

	if (pipe(fd) < 0)
		return (-1);
	node->fd_0 = fd[0];
	node->fd_1 = fd[1];
	return (0);
}

int	create_pipes(t_parc **parc)
{
	t_parc	*node;

	node = *parc;
	while (node != NULL)
	{
		if (pipe_util(node) == -1)
			return (-1);
		node = node->next;
	}
	return (0);
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
	int		status;

	node = *parc;
	prev = NULL;
	i = 0;
	status = 0;
	if (create_pipes(parc) == -1)
	{
		print_error_msg(NULL, NULL, "Pipe error");
		return (-1);
	}
	while (i < ncount)
	{
		pid = fork();
		if (pid < 0)
		{
			print_error_msg(NULL, NULL, "Forking error");
			return (-1);
		}
		if (pid == 0)
		{
			if (i == 0)
			{
				dup2(node->fd_1, 1);
				close_fds(parc);
				status = ft_execute(node, env);
				return (status);
			}
			else if (i == ncount - 1)
			{
				dup2(prev->fd_0, 0);
				close_fds(parc);
				status = ft_execute(node, env);
				return (status);
			}
			else
			{
				dup2(prev->fd_0, 0);
				dup2(node->fd_1, 1);
				close_fds(parc);
				status = ft_execute(node, env);
				return (status);
			}
		}
		prev = node;
		node = node->next;
		i++;
	}
	// parent
	close_fds(parc);
	waitpid(pid, &status, 0);
	//waitpid(pid, NULL, 0);
	//printf("status in execute_proc = %d\n", status);
	return (status);
}

void	print_all_hdoc(t_parc **parc) //remove -> tmp to print last hdocs
{
	t_parc *node;

	node = *parc;
	while (node)
	{
		printf("%s: %s\n", node->cmd, node->hdoc);
		node = node->next;
	}
}

int	execute_pipes(t_parc **parc, t_env **env, int ncount)
{
	pid_t	c_pid;
	int		status;
	//int		wstatus;

	status = 0;
	c_pid = fork();
	if (c_pid < 0)
	{
		print_error_msg(NULL, NULL, "Forking error");
		return (-1);
	}
	else if (c_pid == 0)
	{
		status = execute_proces(parc, env, ncount);
		//printf("status from execute_proc = %d\n", status);
		exit (status);
	}
	else
	{
		waitpid(c_pid, &status, 0);
		//printf("wstatus in fork = %d\n", wstatus);
	}
	return (status);
}

int	start_execute(t_parc **parc, t_env **env)
{
	int		ncount;
	int		status;

	status = 0;
	save_all_hdoc(parc);
	//print_all_hdoc(parc);
	ncount = ft_size_parc(*parc);
	if (ncount == 1)
	{
		status = ft_execute(parc[0], env);
	}
	else
	{
		status = execute_pipes(parc, env, ncount);
	}
	//save exit status in parc
	//printf("status = %d\n", status);
	if (status == -1)
		exit_mini(parc, env);
	return (0);
}
