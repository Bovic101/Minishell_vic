/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_libft.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vodebunm <vodebunm@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 20:17:41 by vodebunm          #+#    #+#             */
/*   Updated: 2024/10/03 23:15:09 by vodebunm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strcat(char *dest, const char *src)
{
	char	*dest_end;

	// Find the end of the destination string
	dest_end = dest;
	while (*dest_end != '\0')
	{
		dest_end++;
	}
	while (*src != '\0')
	{
		*dest_end = *src;
		dest_end++;
		src++;
	}
	*dest_end = '\0';
	return (dest);
}
/** 
//Function to run another minishell program in our  minishell
void run_2nd_minishell(t_parc *parc, t_env **env)
{
    pid_t c_pid;
    int status;
    char **argv;
    char **env_list;

    c_pid = fork();
    if (c_pid == 0)  // In the child process
    {
        argv = arg_to_array_converter(parc->args, parc->cmd); // Convert the arga & env to arrays
        env_list = env_to_array_converter(*env);
        if (execve("./minishell", argv, env_list) == -1)// Execute minishell in the child process
        {
            perror("Minishell execution error");
            free(argv);
            free(env_list);
            exit(EXIT_FAILURE);
        }
    }
    else if (c_pid > 0)
        waitpid(c_pid, &status, 0);//wait for the child (minishell) to finish
    else
        perror("Fork failed");
}*/