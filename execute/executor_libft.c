/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_libft.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vodebunm <vodebunm@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 20:17:41 by vodebunm          #+#    #+#             */
/*   Updated: 2024/09/18 10:11:50 by vodebunm         ###   ########.fr       */
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

char	*str_tokenizer(char *str, const char *delim)
{
	static char	*next_token;
	char		*start;
	char		*end;

	next_token = NULL;
	if (str != NULL)
		next_token = str;
	if (next_token == NULL)
		return (NULL);
	start = next_token;
	while (*start != '\0' && strchr(delim, *start) != NULL)
		start++;
	if (*start == '\0')
	{
		next_token = NULL;
		return (NULL);
	}
	end = start;
	while (*end != '\0' && strchr(delim, *end) == NULL)
		end++;
	if (*end == '\0')
	{
		next_token = NULL;
	}
	else
		*end = '\0';
	next_token = end + 1;
	return (start);
}
/*Function to run another minishell program in our custom minishell*/
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
}
