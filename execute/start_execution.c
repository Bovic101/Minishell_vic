/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 15:46:01 by kdvarako          #+#    #+#             */
/*   Updated: 2024/10/07 14:24:03 by kdvarako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_dup2_node(t_parc *prev, t_parc *node, int i, int ncount)
{
	if (i == 0)
	{
		dup2(node->fd_1, 1);
	}
	else if (i == ncount - 1)
	{
		dup2(prev->fd_0, 0);
	}
	else
	{
		dup2(prev->fd_0, 0);
		dup2(node->fd_1, 1);
	}
}

void	fork_error(t_parc **parc, t_env **env)
{
	print_error_msg(NULL, NULL, "Forking error");
	freeall(env, parc);
	exit(1);
}

void	execution_n_exit(t_parc *node, t_parc **parc, t_env **env)
{
	int	status;

	status = 0;
	close_fds(parc);
	status = ft_execute(node, env);
	freeall(env, parc);
	if (status == -1)
		exit(1);
	exit(status);
}

int	execute_proces(t_parc **parc, t_env **env, int ncount, int status)
{
	t_parc	*node;
	t_parc	*prev;
	int		pid;
	int		i;

	node = *parc;
	prev = NULL;
	i = 0;
	while (i < ncount)
	{
		pid = fork();
		if (pid < 0)
			fork_error(parc, env);
		if (pid == 0)
		{
			ft_dup2_node(prev, node, i, ncount);
			execution_n_exit(node, parc, env);
		}
		prev = node;
		node = node->next;
		i++;
	}
	close_fds(parc);
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}

int	start_execute(t_parc **parc, t_env **env)
{
	int		ncount;
	int		status;

	status = 0;
	save_all_hdoc(parc);
	ncount = ft_size_parc(*parc);
	if (ncount == 1)
	{
		if (ft_strcmp(parc[0]->cmd, "exit") == 0)
			printf("exit\n");
		status = ft_execute(parc[0], env);
	}
	else
	{
		create_pipes(parc, env);
		status = execute_proces(parc, env, ncount, status);
	}
	*env[0]->exit_status = status;
	return (0);
}
