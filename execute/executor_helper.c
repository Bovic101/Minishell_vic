/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vodebunm <vodebunm@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 13:20:14 by vodebunm          #+#    #+#             */
/*   Updated: 2024/09/02 01:20:59 by vodebunm         ###   ########.fr       */
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
	path_env_copy = ft_strdup(path_env);// Create a duplicate of path_env to use with strtok
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

		// check if the command exists and is executable
		if (access(tmp, X_OK) == 0)
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

void redirection_func(t_redirect *in_redir, t_redirect *out_redir)
{
    int fd;

    while (in_redir)
    {
        if (ft_strcmp(in_redir->rtype, "<") == 0)
        {
            fd = open(in_redir->rfile, O_RDONLY);
            if (fd == -1)
            {
                perror("open input redirection");
                exit(EXIT_FAILURE);
            }
            dup2(fd, STDIN_FILENO); // Redirect stdin to the file
            close(fd);
        }
        in_redir = in_redir->next;
    }
    while (out_redir)
    {
        if (ft_strcmp(out_redir->rtype, ">") == 0)
        {
            fd = open(out_redir->rfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd == -1)
            {
                perror("open output redirection");
                exit(EXIT_FAILURE);
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        else if (ft_strcmp(out_redir->rtype, ">>") == 0)
        {
            fd = open(out_redir->rfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd == -1)
            {
                perror("open output redirection (append)");
                exit(EXIT_FAILURE);
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        out_redir = out_redir->next;
    }
}


/* 
 * Function to create pipes between commands.
 * fork processes
 * manage i/o redir
 **/
void	pipe_func(t_parc *command, t_env **env)
{
	t_parc *cur_command;
	int fd_pipe[2];
	int input_fd;
	pid_t pid;
	int status;

	cur_command = command;
	input_fd = 0;
	while (cur_command)
	{
		if (cur_command->next) // create pipe if there's a next command
		{
			if (pipe(fd_pipe) == -1)
			{
				perror("pipe creation error");
				exit(EXIT_FAILURE);
			}
		}
		pid = fork(); // fork new process for command
		if (pid == -1)
		{
			perror("child process creation error");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			if (input_fd != 0)
			{
				dup2(input_fd, 0);
				close(input_fd);
			}
			if (cur_command->next)
			{
				dup2(fd_pipe[1], 1);
				close(fd_pipe[1]);
				close(fd_pipe[0]);
			}
			redirection_func(cur_command->redirs_in, cur_command->redirs_out);
			executor_func(cur_command, env);
		}
		else
		{
			waitpid(pid, &status, 0);
			if (input_fd != 0)
			{
				close(input_fd);
			}
			if (cur_command->next)
			{
				close(fd_pipe[1]);
				input_fd = fd_pipe[0];
			}
			cur_command = cur_command->next;
		}
	}
}
