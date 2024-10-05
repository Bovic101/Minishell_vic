/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 12:41:29 by kdvarako          #+#    #+#             */
/*   Updated: 2024/10/05 15:47:03 by kdvarako         ###   ########.fr       */
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

void	create_pipes(t_parc **parc, t_env **env)
{
	t_parc	*node;

	node = *parc;
	while (node != NULL)
	{
		if (pipe_util(node) == -1)
		{
			print_error_msg(NULL, NULL, "Pipe error");
			freeall(env, parc);
			exit(1);
		}
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
