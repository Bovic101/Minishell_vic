/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vodebunm <vodebunm@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 13:19:40 by vodebunm          #+#    #+#             */
/*   Updated: 2024/10/08 03:17:22 by vodebunm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/** Helper function to free a null-terminated array of strings */
void	free_string_array(char **arr)
{
	int	i;

	i = 0;
	if (arr)
	{
		while (arr[i])
		{
			free(arr[i]);
			i++;
		}
		free(arr);
	}
}

/** Function that converts args and env variables to arrays
 * and finds the command path. */
char	*prepare_command(t_parc *command, t_env **env, char ***argv,
		char ***env_list)
{
	char	*command_path;

	*argv = arg_to_array_converter(command->args, command->cmd);
	*env_list = env_to_array_converter(*env);
	if (!*argv || !*env_list)
	{
		perror("Memory allocation failed");
		free_string_array(*argv);
		free_string_array(*env_list);
		exit(EXIT_FAILURE);
	}
	if (command->cmd[0] == '/' || command->cmd[0] == '.')
	{
		command_path = ft_strdup(command->cmd);
	}
	else
	{
		command_path = command_fullpath_finder(command->cmd, env);
	}
	return (command_path);
}

void	executor_func(t_parc *command, t_env **env)
{
	char	**argv;
	char	**env_list;
	char	*command_path;

	command_path = prepare_command(command, env, &argv, &env_list);
	if (command_path != NULL && access(command_path, X_OK) == 0)
	{
		if (execve(command_path, argv, env_list) == -1)
		{
			perror("execve failed");
			free_string_array(argv);
			free_string_array(env_list);
			free(command_path);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		handle_error_msg(command->cmd);
		free_string_array(argv);
		free_string_array(env_list);
		free(command_path);
		exit(127);
	}
}

void	handle_error_msg(const char *cmd)
{
	const char	*error_msg;

	error_msg = "Command not found: ";
	write(STDERR_FILENO, error_msg, ft_strlen(error_msg));
	write(STDERR_FILENO, cmd, ft_strlen(cmd));
	write(STDERR_FILENO, "\n", 1);
}
