/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vodebunm <vodebunm@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 12:26:11 by kdvarako          #+#    #+#             */
/*   Updated: 2024/09/24 23:18:48 by vodebunm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_processing(char *s, t_env **env)
{
	t_token	*token;
	t_parc	*parc;

	token = NULL;
	parc = NULL;

	lexer(&token, s);
	parcer(&token, &parc, env);
	if (parc && parc->cmd != NULL && ft_strcmp(parc->cmd, "./minishell") == 0)//check if the cmd is minishell
	{
		run_2nd_minishell(parc, env);
	}
	start_execute(&parc, env);
	//main_pipe_proc(&parc, env); //handle pipes & exec cmd in child process
	freeall(&token, &parc);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char		*s;
	t_env		*env;
	//t_history	*history;
	int			loop_condition;

	loop_condition = 0;
	(void)argc;
	(void)argv;
	env = NULL;
	//history = NULL;
	save_environment(envp, &env);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
	while (!loop_condition)
	{
		s = readline("Our_shell:~$ ");
		if (s == NULL) // Handle Ctrl+D (EOF)
		{
			loop_condition = 1;
			continue ; // Avoid further processing if s is NULL
		}
		if (*s)//Non_empty input
		{
			add_history(s); // Only add to history
			if (unclosed_quote_checker(s) != 0) //check unclosed quote before cmd processing
			{
				free(s);
				continue;
			}
			
			if (ft_strcmp(s, "exit") == 0)
			{
				free(s);
				loop_condition = 1;
				continue ;
			}
			cmd_processing(s, &env);
		}
		free(s);
	}
	ft_free_env(&env);
	//ft_free_history(&history);
	return (0);
}
