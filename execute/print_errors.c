/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:35:11 by kdvarako          #+#    #+#             */
/*   Updated: 2024/10/02 14:10:20 by kdvarako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/*
void	save_exit_status_parc(t_parc **parc, int *exit_status)
{
	t_parc	*node;

	node = *parc;
	while (node)
	{
		node->exit_status = exit_status;
		node = node->next;
	}
}
*/

void	print_error_msg(char *cmd, char *arg, char *msg)
{
	//write(STDERR_FILENO, ...);
	if (cmd != NULL)
	{
		write(2, cmd, ft_strlen(cmd));
		write(2, ": ", 2);
	}
	if (arg != NULL)
	{
		write(2, arg, ft_strlen(arg));
		write(2, ": ", 2);
	}
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
}

/*
int	exit_mini(t_parc **parc, t_env **env)
{
	ft_free_parc(parc);
	ft_free_env(env);
	exit(1);
}
*/
