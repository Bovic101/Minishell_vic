/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 12:41:29 by kdvarako          #+#    #+#             */
/*   Updated: 2024/09/30 12:36:55 by kdvarako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* 
 * Function to create pipes between child proces
 */

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
				//if (node->redirs_out != NULL)
				//{
					//write(2, "!\n", 2);
					//redir_out(node);
				//}
				//else
					dup2(node->fd_1, 1);
				close_fds(parc);
				ft_execute(node, env);
				return (0);
			}
			else if (i == ncount - 1)
			{
				dup2(prev->fd_0, 0);
				//if (node->redirs_out != NULL)
					//redir_out(node);
				close_fds(parc);
				ft_execute(node, env);
				return (0);
			}
			else
			{
				dup2(prev->fd_0, 0);
				//if (node->redirs_out != NULL)
					//redir_out(node);
				//else
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

int	start_execute(t_parc **parc, t_env **env)
{
	int ncount;
	pid_t	c_pid;
	int		status;
	
	save_all_hdoc(parc);
	//print_all_hdoc(parc);
	ncount = ft_size_parc(*parc);
	if (ncount == 1)
	{
		ft_execute(parc[0], env);
	}
	else
	{
		c_pid = fork();  //if needed??
		if (c_pid == 0)
		{
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
