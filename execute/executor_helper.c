/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vodebunm <vodebunm@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 13:20:14 by vodebunm          #+#    #+#             */
/*   Updated: 2024/08/27 14:26:11 by vodebunm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
execve() function requires array to execute a commannd
**/
// convert linked_lst of arg(t_arg) to an array of strings
char	**arg_to_array_converter(t_arg *arg, char *command)
{
	int		i;
	char	**argv;
	t_arg	*cur_arg;

	int arg_counter = 1; // starting from 1 as a first command
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

////convert linked_lst of environment var (t_env) to an array of strings
char	**env_to_array_converter(t_arg *env)
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
				+ ft_strlen(cur_env->value) + 2);
		// allocate memory to the key=value str
		if (!env_array[i])
			return (NULL);
		ft_strcpy(env_array[i], cur_env->key); // copy key To do
		ft_strcat(env_array[i], "=");          // To do
		ft_strcat(env_array[i], cur_env->value);
		cur_env = cur_env->next; // move to next var in the list
		i++;
	}
	env_array[i] = NULL; // end of array
	return (env_array);
}
// Locate the full path in which a command is stored in directories listed in PATH env-var
char	*command_fullpath_finder(char *command, t_env **env)
{
	char *path_env;
	char *complete_path;
	char *tmp;
	char *path;
	if (path_env == NULL)
	{
		write(2, "PATH environment variable not found\n", 36);
		return (NULL);
	}
}