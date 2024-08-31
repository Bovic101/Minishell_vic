/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vodebunm <vodebunm@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 13:20:14 by vodebunm          #+#    #+#             */
/*   Updated: 2024/08/30 22:25:59 by vodebunm         ###   ########.fr       */
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
	
	path_env = get_value("PATH",env);
	char complete_path = NULL;
	
	if (path_env == NULL)
	{
		write(2, "PATH environment variable not found\n", 36);
		return (NULL);
	}
	
	path = strtok(path_env, ":");//To do;
	
	while (path != NULL)
	{
		tmp = malloc(ft_strlen(path) + ft_strlen(command) + 2);//use for slach and null terminator
		if (!tmp)
		{
			perror("Failure to allocate full path");
			return(NULL);
		}
		//implementation done manually
		ft_strcpy(tmp,path);//copy dir path
		ft_strcat(tmp, "/");//append a slash
		ft_strcat(tmp, command);
		//check if the cmd exits and is executable
		if (access(tmp, X_OK) == 0)
		{
			complete_path = tmp;
			break;
		}
		free(tmp);
		path = strtok(NULL, ":");//to do
	}
	return(complete_path);
}

void	redirection_func(t_redirect *redir)
{
	t_redirect *cur_redir;
	int fd;
	
	cur_redir = redir;
	//
	while (cur_redir)
	{
		if (ft_strcmp(cur_redir->rtype, "<")== 0)//input redirs
		{
			fd=open(cur_redir->rfile, O_RDONLY);
			if (fd == -1)
			{
				perror("open input redirection");
				exit(EXIT_FAILURE);
			}
			dup2(fd,0); //redir s/0 to the file
			close(fd);
		}
		else if (ft_strcmp(cur_redir->rtype, ">") == 0)//output redir
		{
			fd=open(cur_redir->rfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
			{
				perror("open output redirection");
				exit(EXIT_FAILURE);
			}
			dup2(fd, 1);
			close(fd);
		}
		else if (ft_strcmp(cur_redir->rtype, ">>")==0)
		{
			fd = open(cur_redir->rfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd == -1)
			{
				perror("open file for append redirection");
				exit(EXIT_FAILURE);
			}
			dup2(fd, 1);
			close(fd);
		}
		cur_redir = cur_redir->next;
	}
}
