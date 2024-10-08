/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_locator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vodebunm <vodebunm@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 02:47:40 by vodebunm          #+#    #+#             */
/*   Updated: 2024/10/08 03:00:54 by vodebunm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* Function retrieves the PATH environment variable */
char	*get_path_env(t_env **env)
{
	char	*path_env;

	path_env = get_value("PATH", env);
	if (!path_env)
		write(2, "PATH not found\n", 15);
	return (path_env);
}

/* Function duplicates the PATH environment variable */
char	*dup_path_env(char *path_env)
{
	char	*path_env_copy;

	path_env_copy = ft_strdup(path_env);
	if (!path_env_copy)
		perror("Failed to duplicate PATH");
	return (path_env_copy);
}

/* Function searches for the command in directories in PATH */
char	*search_path(char *command, char *path_env_copy)
{
	char	*tmp;
	char	*path;
	int		len;
	int		i;

	i = 0;
	while (path_env_copy[i] != '\0')
	{
		path = &path_env_copy[i];
		while (path_env_copy[i] != ':' && path_env_copy[i] != '\0')
			i++;
		len = i - (path - path_env_copy);
		tmp = malloc(len + ft_strlen(command) + 2);
		if (!tmp)
			return (perror("Memory allocation failed"), NULL);
		ft_strncpy(tmp, path, len);
		tmp[len] = '/';
		ft_strcpy(&tmp[len + 1], command);
		if (access(tmp, X_OK) == 0)
			return (tmp);
		free(tmp);
		if (path_env_copy[i] != '\0')
			i++;
	}
	return (NULL);
}

/* Function finds the full path of the command */
char	*command_fullpath_finder(char *command, t_env **env)
{
	char	*path_env;
	char	*path_env_copy;
	char	*complete_path;

	path_env = get_path_env(env);
	if (!path_env)
		return (NULL);
	path_env_copy = dup_path_env(path_env);
	if (!path_env_copy)
		return (NULL);
	complete_path = search_path(command, path_env_copy);
	free(path_env_copy);
	return (complete_path);
}
