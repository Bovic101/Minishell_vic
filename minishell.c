/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 12:26:11 by kdvarako          #+#    #+#             */
/*   Updated: 2024/10/05 18:26:38 by kdvarako         ###   ########.fr       */
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

int	main(int argc, char **argv, char **envp)
{
	char		*s;
	t_env		*env;
	int			exit_status;

	exit_status = 0;
	(void)argc;
	(void)argv;
	env = NULL;
	save_environment(envp, &env, &exit_status);
	signal_handlers_caller();
	while (true)
	{
		s = readline("Our_shell:~$ ");
		if (*s)
		{
			add_history(s);
			if (unclosed_quote_checker(s) != 0)
				free(s);
			else
				cmd_processing(s, &env);
		}
	}
	ft_free_env(&env);
	return (exit_status);
}
