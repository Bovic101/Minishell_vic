/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 12:26:11 by kdvarako          #+#    #+#             */
/*   Updated: 2024/09/16 12:26:57 by kdvarako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_processing(char *s, t_env **env)
{
	t_token	*token;
	t_parc	*parc;
	pid_t	c_pid;
	int		status;

	token = NULL;
	parc = NULL;
	lexer(&token, s);
	parcer(&token, &parc, env);
	c_pid = fork(); // Fork a new child_process to execute the command
	if (c_pid == 0)
	{
		main_pipe_proc(&parc, env);
		//executor_func(parc, env);
		freeall(&token, &parc);
		exit(0);
	}
	else if (c_pid > 0) // Parent process
	{
		waitpid(c_pid, &status, 0);
	}
	else
		perror("forking process failed");
	freeall(&token, &parc);
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
		if (*s)
		{
			add_history(s);
			// Only add to history and process command if there's valid input
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
