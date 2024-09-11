/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vodebunm <vodebunm@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 13:19:40 by vodebunm          #+#    #+#             */
/*   Updated: 2024/09/11 12:27:28 by vodebunm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
// function to convert cmd args & env in the linked list to array, find cmd path & exec
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
	
	command_path = command_fullpath_finder(command->cmd, env); // Find the full path of the command
	if (command_path == NULL)
	{
		handle_error_msg(command->cmd);
		free(argv);
		free(env_list);
		return;
	}
	if (execve(command_path, argv, env_list) == -1)// Execute the command using execve()
	{
		perror("execve failed");
		free(argv);
		free(env_list);
		free(command_path);
		exit(EXIT_FAILURE);  // Only the child process should exit
	}
	free(argv);
	free(env_list);
	free(command_path);
}
  /* Handle redirections before executing the command
  *and execute the command + redirs
  */
void redir_execute_command(t_parc *command, t_env **env)
{
  
    if (command->redirs_in|| command->redirs_out)
    {
        redirection_func(command->redirs_in, command->redirs_out);
    }
    executor_func(command, env);
}
void handle_error_msg(const char *cmd)
{
    const char *error_msg;
    error_msg = "Command not found: ";

    write(STDERR_FILENO, error_msg, ft_strlen(error_msg));
    write(STDERR_FILENO, cmd, ft_strlen(cmd));
    write(STDERR_FILENO, "\n", 1);
    exit(EXIT_FAILURE);
}
