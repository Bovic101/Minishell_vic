/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vodebunm <vodebunm@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 12:56:13 by vodebunm          #+#    #+#             */
/*   Updated: 2024/09/15 00:10:59 by vodebunm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
void	prompt(void)
{
	printf("Our_shell$");
}
**/

void	sigint_handler(int signal)
{
	(void)signal;
	write(STDOUT_FILENO, "\nOur_shell:~$ ", 15);
}

void	sigquit_handler(int signal)
{
	(void)signal;
	printf("SIGQUIT SIGNAL RECEIVED");
}