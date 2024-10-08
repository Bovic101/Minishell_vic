/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vodebunm <vodebunm@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 12:56:13 by vodebunm          #+#    #+#             */
/*   Updated: 2024/10/08 03:33:10 by vodebunm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <signal.h>

void	sigint_handler(int signal)
{
	(void)signal;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	sigquit_handler(int signal)
{
	(void)signal;
}

int	eof_handler(int count, int key)
{
	(void)key;
	if (count == 0)
	{
		printf("\nexit\n");
		exit(0);
		return (0);
	}
	return (0);
}

/**Set up signal handlers*/
void	signal_handlers_caller(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	ft_memset(&sa_int, 0, sizeof(sa_int));
	ft_memset(&sa_quit, 0, sizeof(sa_quit));
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_handler = sigint_handler;
	sa_int.sa_flags = 0;
	sigaction(SIGINT, &sa_int, NULL);
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_handler = SIG_IGN;
	sa_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_quit, NULL);
}
