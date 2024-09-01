/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vodebunm <vodebunm@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 13:19:40 by vodebunm          #+#    #+#             */
/*   Updated: 2024/09/02 00:32:14 by vodebunm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
// function to convert cmd args & env in the linked list to array, find cmd path & exec
void	executor_func(t_parc *command, t_env **env)
{
	char **argv;
	char **env_list; // corrected to char**
	char *command_path;
	char *error_msg;

	argv = arg_to_array_converter(command->args, command->cmd);
	env_list = env_to_array_converter(*env);
	if (!argv || !env_list)
	{
		perror("Memory allocation failed");
		free(argv);
		free(env_list);
		exit(EXIT_FAILURE);
	}

	command_path = command_fullpath_finder(command->cmd, env);
	if (command_path == NULL)
	{
		error_msg = "Command not found: ";
		write(STDERR_FILENO, error_msg, ft_strlen(error_msg));
		write(STDERR_FILENO, command->cmd, ft_strlen(command->cmd));
		write(STDERR_FILENO, "\n", 1);
		free(argv);
		free(env_list);
		exit(EXIT_FAILURE);
	}
	if (execve(command_path, argv, env_list) == -1)
	{
		perror("execve");
		free(argv);
		free(env_list);
		free(command_path);
		exit(EXIT_FAILURE);
	}
	free(argv);
	free(env_list);
	free(command_path);
}
