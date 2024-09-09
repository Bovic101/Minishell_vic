/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vodebunm <vodebunm@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 12:56:13 by vodebunm          #+#    #+#             */
/*   Updated: 2024/09/09 15:26:28 by vodebunm         ###   ########.fr       */
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
	printf("\n");
	printf("Our_shell:~$ "); // Re-display the prompt
}

void	sigquit_handler(int signal)
{
	(void)signal;
	printf("SIGQUIT SIGNAL RECEIVED");
}