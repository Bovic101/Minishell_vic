/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vodebunm <vodebunm@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 13:20:14 by vodebunm          #+#    #+#             */
/*   Updated: 2024/09/15 14:44:08 by vodebunm         ###   ########.fr       */
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

	arg_counter = 1; // starting from 1 as the first element is the command
	cur_arg = arg;
	while (cur_arg)
	{
		arg_counter++;
		cur_arg = cur_arg->next;
	}
	argv = (char **)malloc(sizeof(char *) * (arg_counter + 1));
	if (!argv)
	{
		return (NULL);
	}
	argv[0] = command;
	cur_arg = arg;
	i = 1;
	while (cur_arg)
	{
		argv[i++] = cur_arg->value;
		cur_arg = cur_arg->next;
	}
	argv[i] = NULL; // end of array
	return (argv);
}
//// convert linked list of environment var (t_env) to an array of strings
char	**env_to_array_converter(t_env *env) // Corrected t_arg to t_env
{
	int		i;
	int		env_var_count;
	t_env	*cur_env;
	char	**env_array;

	env_var_count = 0;
	cur_env = env;
	while (cur_env)
	{
		env_var_count++;
		cur_env = cur_env->next;
	}
	env_array = (char **)malloc(sizeof(char *) * (env_var_count + 1));
	if (!env_array)
		return (NULL);
	cur_env = env;
	i = 0;
	while (cur_env)
	{
		env_array[i] = (char *)malloc(ft_strlen(cur_env->key)
				+ ft_strlen(cur_env->value) + 2); // +2 for '=' and null term
		if (!env_array[i])
		{
			while (i > 0)
				free(env_array[--i]);
			free(env_array);
			return (NULL);
		}
		ft_strcpy(env_array[i], cur_env->key);
		ft_strcat(env_array[i], "=");
		ft_strcat(env_array[i], cur_env->value);
		cur_env = cur_env->next;
		i++;
	}
	env_array[i] = NULL; // end of array
	return (env_array);
}

// Locate the full path in which a command is stored in directories listed in PATH env-var
char	*command_fullpath_finder(char *command, t_env **env)
{
	char	*path_env;
	char	*complete_path;
	char	*tmp;
	char	*path;
	char	*path_env_copy;

	path_env = get_value("PATH", env);
	complete_path = NULL;
	if (path_env == NULL)
	{
		write(2, "PATH environment variable not found\n", 36);
		return (NULL);
	}
	path_env_copy = ft_strdup(path_env);// Create a duplicate of path_env to use with str_token
	if (!path_env_copy)
	{
		perror("Failed to duplicate PATH environment variable");
		return (NULL);
	}

	path = strtok(path_env_copy, ":");
	while (path != NULL)
	{
		tmp = malloc(ft_strlen(path) + ft_strlen(command) + 2); // +2 for '/' and null terminator
		if (!tmp)
		{
			perror("Failure to allocate memory for full path");
			free(path_env_copy);
			return (NULL);
		}
		ft_strcpy(tmp, path);   // copy dir path
		ft_strcat(tmp, "/");    // append a slash
		ft_strcat(tmp, command); // append the command
		if (access(tmp, X_OK) == 0)// check if the command exists and is executable
		{
			complete_path = tmp;
			break;
		}
		free(tmp);
		path = strtok(NULL, ":");
	}
	free(path_env_copy);
	return (complete_path);
}

