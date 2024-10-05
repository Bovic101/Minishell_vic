/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vodebunm <vodebunm@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 13:20:14 by vodebunm          #+#    #+#             */
/*   Updated: 2024/10/05 17:35:59 by vodebunm         ###   ########.fr       */
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
		return (NULL);
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
/* get the total number of environment variables 
before allocating memory for the array*/

int count_env_vars(t_env *env)
{
	int count;
	
	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return(count);
}

/**Convert linked list of environment var (t_env) to an array of strings */
char **env_to_array_converter(t_env *env)
{
	int		i;
	t_env	*cur_env;
	char	**env_array;

	i = 0;
	cur_env = env;
	if (!(env_array = (char **)malloc(sizeof(char *) * (count_env_vars(env) + 1))))
		return (NULL);
	while (cur_env)
	{
		if (!(env_array[i] = (char *)malloc(ft_strlen(cur_env->key) + ft_strlen(cur_env->value) + 2)))
		{
			while (i > 0)
				free(env_array[--i]);
			free(env_array);
			return (NULL);
		}
		ft_strcpy(env_array[i], cur_env->key);
		ft_strcat(env_array[i], "=");
		ft_strcat(env_array[i++], cur_env->value);
		cur_env = cur_env->next;
	}
	env_array[i] = NULL;
	return (env_array);
}

/*Function to search forcommand in the directories specified by 
the PATH environment variable.*/
char	*find_in_path_env(char *command, char *path_env_copy)
{
	char	*tmp;
	char	*path;
	char	*complete_path = NULL;

	path = strtok(path_env_copy, ":");
	while (path != NULL)
	{
		tmp = malloc(ft_strlen(path) + ft_strlen(command) + 2); // +2 for '/' and null terminator
		if (!tmp)
		{
			perror("Failure to allocate memory for full path");
			return (NULL);
		}
		ft_strcpy(tmp, path);   // copy dir path
		ft_strcat(tmp, "/");    // append a slash
		ft_strcat(tmp, command); // append the command
		if (access(tmp, X_OK) == 0) // check if the command exists and is executable
		{
			complete_path = tmp;
			break;
		}
		free(tmp);
		path = strtok(NULL, ":");
	}
	return (complete_path);
}
/**Funtion retriev the PATH environment variable,
 * calls (find_in_path_env) to search cmd*/
char	*command_fullpath_finder(char *command, t_env **env)
{
	char	*path_env;
	char	*complete_path;
	char	*path_env_copy;

	path_env = get_value("PATH", env);
	if (path_env == NULL)
	{
		write(2, "PATH environment variable not found\n", 36);
		return (NULL);
	}
	path_env_copy = ft_strdup(path_env); // Create a duplicate of path_env to use with str_token
	if (!path_env_copy)
	{
		perror("Failed to duplicate PATH environment variable");
		return (NULL);
	}
	complete_path = find_in_path_env(command, path_env_copy);
	free(path_env_copy);
	return (complete_path);
}

