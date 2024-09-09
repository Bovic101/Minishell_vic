/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vodebunm <vodebunm@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 12:26:11 by kdvarako          #+#    #+#             */
/*   Updated: 2024/09/09 08:56:03 by vodebunm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void cmd_processing(char *s, t_env **env)
{
    t_token *token = NULL;
    t_parc *parc = NULL;

    lexer(&token, s);
    parcer(&token, &parc, env);
    //execute(&parc, env);
    executor_func(parc, env);
    freeall(&token, &parc);
}

int main(int argc, char **argv, char **envp)
{
    char *s;
    t_env *env;
    t_history *history;
    int loop_condition = 0;

    (void)argc;
    (void)argv;

    env = NULL;
    history = NULL;

    save_environment(envp, &env);
    signal(SIGINT, sigint_handler); // Signal call for Ctrl+C
    signal(SIGQUIT, sigquit_handler);

    while (!loop_condition)
    {
        s = readline("Our_shell:~$ ");
        if (s == NULL) // Handle Ctrl+D
        {
            loop_condition = 1;
        }
        else if (*s == '\0') // Redisplay cmd when enter is pressed
        {
            free(s);
        }
        else if (ft_strcmp(s, "exit") == 0) // Exit the shell if the user types "exit"
        {
            free(s);
            loop_condition = 1;
        }
        else
        {
            save_history(s, &history);
            cmd_processing(s, &env);
            free(s);
        }
    }
    
    ft_free_env(&env);
    ft_free_history(&history);
    return 0;
}


