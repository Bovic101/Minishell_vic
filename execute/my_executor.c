/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vodebunm <vodebunm@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 13:19:40 by vodebunm          #+#    #+#             */
/*   Updated: 2024/09/27 21:57:05 by vodebunm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
 * Function to execute external commands by converting arguments and env to arrays
 * Finds the full path of the command and then executes it.
 */
void	executor_func(t_parc *command, t_env **env)
{
	char	**argv;
	char	**env_list;
	char	*command_path;

	argv = arg_to_array_converter(command->args, command->cmd);
	env_list = env_to_array_converter(*env);
	if (!argv || !env_list)
	{
		perror("Memory allocation failed");
		free(argv);
		free(env_list);
		exit(EXIT_FAILURE);
	}
	if (command->cmd[0] == '/' || command->cmd[0] == '.') // If the command is absolute/relative path
	{
		command_path = ft_strdup(command->cmd);
	}
	else
	{
		command_path = command_fullpath_finder(command->cmd, env); // Find the full path of the cmd in the PATH environment var
	}
	if (command_path != NULL && access(command_path, X_OK) == 0)// If the command path was found, it's executable
	{
		if (execve(command_path, argv, env_list) == -1)
		{
			perror("execve failed");
			free(argv);
			free(env_list);
			free(command_path);
			exit(EXIT_FAILURE); //child process should exit
		}
	}
	else
		handle_error_msg(command->cmd);// if cmd not found
	free(argv);
	free(env_list);
	free(command_path);
}

void	handle_error_msg(const char *cmd)
{
	const char	*error_msg;

	error_msg = "Command not found: ";
	write(STDERR_FILENO, error_msg, ft_strlen(error_msg));
	write(STDERR_FILENO, cmd, ft_strlen(cmd));
	write(STDERR_FILENO, "\n", 1);
	exit(EXIT_FAILURE);
}
