/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vodebunm <vodebunm@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 12:26:11 by kdvarako          #+#    #+#             */
/*   Updated: 2024/09/01 23:02:57 by vodebunm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_processing(char *s, t_env **env)
{
	t_token		*token;
	t_parc		*parc;

	token = NULL;
	parc = NULL;
	lexer(&token, s);
	//ft_lst_print(&token);
	parcer(&token, &parc, env);
	ft_plst_print(&parc);
	//execute(&parc, env);
	executor_func(&parc, env);
	freeall(&token, &parc);
}

int	main(int argc, char **argv, char **envp)
{
	char		*s;
	int			i;
	t_env		*env;
	t_history	*history;

	env = NULL;
	history = NULL;
	i = 0;
	save_environment(envp, &env);
	while (i < 2)
	{
		/*
		ft_env_print(&env);
		printf("______________________________\n");
		ft_env_sort_declare(env);
		*/
		s = readline(">> ");
		save_history(s, &history);
		cmd_processing(s, &env);
		free(s);
		s = NULL;
		i++;
	}
	ft_history_print(&history);
	ft_free_env(&env);
	ft_free_history(&history);
	return (0);
}
