/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 13:19:40 by vodebunm          #+#    #+#             */
/*   Updated: 2024/10/05 13:03:10 by kdvarako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
 * Function to execute external commands by converting arguments and env to arrays
 * Finds the full path of the command and then executes it.
 */
void executor_func(t_parc *command, t_env **env)
{
    char **argv;
    char **env_list;
    char *command_path;

    argv = arg_to_array_converter(command->args, command->cmd);
    env_list = env_to_array_converter(*env);

    if (!argv || !env_list)
    {
        perror("Memory allocation failed");
        free(argv);
        free(env_list);
        exit(EXIT_FAILURE);
    }

    if (command->cmd[0] == '/' || command->cmd[0] == '.')
    {
        command_path = ft_strdup(command->cmd);  // Absolute or relative path
    }
    else
    {
        command_path = command_fullpath_finder(command->cmd, env);  // Search in PATH
    }
    if (command_path != NULL && access(command_path, X_OK) == 0)// If the command was found and is executable
    {
        if (execve(command_path, argv, env_list) == -1)
        {
            perror("execve failed");
            free(argv);
            free(env_list);
            free(command_path);
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        // Command not found: Print error message and exit with status 127
        handle_error_msg(command->cmd);  // Call the error printing function
        free(argv);
        free(env_list);
        free(command_path);
        exit(127);  // Set the exit code to 127 for "command not found"
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
