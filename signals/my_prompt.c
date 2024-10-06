/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vodebunm <vodebunm@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 12:56:13 by vodebunm          #+#    #+#             */
/*   Updated: 2024/10/06 10:10:19 by vodebunm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <signal.h>

void sigint_handler(int signal)
{
	(void)signal;
	write(STDOUT_FILENO, "\n",1);
	rl_replace_line("", 0);
	rl_on_new_line();//func inform readline that user pressed ctrl +c
    /**rl_point= 0;//manually clearing the input
    rl_end=0;*/
	rl_redisplay();//func redsisplay the prompt
}

void	sigquit_handler(int signal)
{
	(void)signal;
	exit(0);
}

int eof_handler(int count, int key) 
{
	(void)key;
	if (count == 0)  // If the line is empty (count is 0 when hit Ctrl-D 
	{
        printf("\nexit\n");
        exit(0);
        return 0; // Return a value
    }
    return 0;
}

// Set up signal handlers
void signal_handlers_caller()
{
	struct sigaction sa_int;
	struct sigaction sa_quit;
	
	ft_memset(&sa_int, 0, sizeof(sa_int));
	ft_memset(&sa_quit, 0, sizeof(sa_quit));

	sigemptyset(&sa_int.sa_mask);  // Set up SIGQUIT handler (Ctrl + c)
	sa_int.sa_handler = sigint_handler;
	sa_int.sa_flags = 0;
	sigaction(SIGINT, &sa_int, NULL);

	sigemptyset(&sa_quit.sa_mask); // Set up SIGQUIT handler (Ctrl-\)
	sa_quit.sa_handler = sigquit_handler;
	sa_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_quit, NULL);
}
