/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vodebunm <vodebunm@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 12:26:11 by kdvarako          #+#    #+#             */
/*   Updated: 2024/10/08 03:38:28 by vodebunm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_processing(char *s, t_env **env)
{
	t_token	*token;
	t_parc	*parc;

	if (s == NULL)
		return (0);
	token = NULL;
	parc = NULL;
	lexer(&token, s);
	parcer(&token, &parc, env);
	ft_free_token(&token);
	free(s);
	start_execute(&parc, env);
	ft_free_parc(&parc);
	return (0);
}

/* Implements cmd loop for the shell, wait for user input,
 processing cmd, and managing history*/

void	shell_loop(t_env **env)
{
	char	*s;
	int		loop_condition;

	s = NULL;
	loop_condition = 0;
	while (!loop_condition)
	{
		s = readline("Our_shell:~$ ");
		if (s == NULL)
			loop_condition = 1;
		else if (*s)
		{
			add_history(s);
			if (unclosed_quote_checker(s) != 0)
				free(s);
			else
				cmd_processing(s, env);
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;
	int		exit_status;

	(void)argc;
	(void)argv;
	env = NULL;
	exit_status = 0;
	save_environment(envp, &env, &exit_status);
	signal_handlers_caller();
	shell_loop(&env);
	ft_free_env(&env);
	return (exit_status);
}
