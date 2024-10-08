/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vodebunm <vodebunm@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 13:20:14 by vodebunm          #+#    #+#             */
/*   Updated: 2024/10/08 02:52:40 by vodebunm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
execve() function requires array to execute a command
**/
// convert linked list of arg (t_arg) to an array of strings
char	**arg_to_array_converter(t_arg *arg, char *command)
{
	int		i;
	char	**argv;
	t_arg	*cur_arg;
	int		arg_counter;

	arg_counter = 1;
	cur_arg = arg;
	while (cur_arg)
	{
		arg_counter++;
		cur_arg = cur_arg->next;
	}
	argv = (char **)malloc(sizeof(char *) * (arg_counter + 1));
	if (!argv)
		return (NULL);
	argv[0] = command;
	cur_arg = arg;
	i = 1;
	while (cur_arg)
	{
		argv[i++] = cur_arg->value;
		cur_arg = cur_arg->next;
	}
	argv[i] = NULL;
	return (argv);
}
/* get the total number of environment variables
before allocating memory for the array*/

int	count_env_vars(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

char	*create_env_string(t_env *env)
{
	char	*env_string;
	int		total_len;

	total_len = ft_strlen(env->key) + ft_strlen(env->value) + 2;
	env_string = malloc(total_len);
	if (!env_string)
		return (NULL);
	ft_strcpy(env_string, env->key);
	ft_strcat(env_string, "=");
	ft_strcat(env_string, env->value);
	return (env_string);
}

char	**free_env_array(char **env_array, int i)
{
	while (i > 0)
		free(env_array[--i]);
	free(env_array);
	return (NULL);
}

char	**env_to_array_converter(t_env *env)
{
	int		i;
	int		env_count;
	char	**env_array;

	i = 0;
	env_count = count_env_vars(env);
	env_array = malloc(sizeof(char *) * (env_count + 1));
	if (!env_array)
		return (NULL);
	while (env)
	{
		env_array[i] = create_env_string(env);
		if (!env_array[i])
			return (free_env_array(env_array, i));
		env = env->next;
		i++;
	}
	env_array[i] = NULL;
	return (env_array);
}
