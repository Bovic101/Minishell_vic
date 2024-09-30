/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 12:26:11 by kdvarako          #+#    #+#             */
/*   Updated: 2024/09/30 16:11:57 by kdvarako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_processing(char *s, t_env **env, int *exit_status)
{
	t_token	*token;
	t_parc	*parc;

	token = NULL;
	parc = NULL;

	lexer(&token, s);
	parcer(&token, &parc, env, exit_status);
	ft_free_token(&token);
	//ft_plst_print(&parc);
	//we don't need this part anymore ?
	/*if (parc && parc->cmd != NULL && ft_strcmp(parc->cmd, "./minishell") == 0)//check if the cmd is minishell
	{
		run_2nd_minishell(parc, env);
		freeall(&token, &parc);
		return(0);
	}*/
	start_execute(&parc, env);
	ft_free_parc(&parc);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char		*s;
	t_env		*env;
	int			loop_condition;
	int			exit_status;

	loop_condition = 0;
	exit_status = 0;
	(void)argc;
	(void)argv;
	env = NULL;
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
				continue ;
			}
			if (ft_strcmp(s, "exit") == 0)
			{
				free(s);
				loop_condition = 1;
				continue ;
			}
			cmd_processing(s, &env, &exit_status);
		}
		free(s);
	}
	ft_free_env(&env);
	return (exit_status);
}
