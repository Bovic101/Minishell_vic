/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 11:49:12 by kdvarako          #+#    #+#             */
/*   Updated: 2024/10/07 11:53:13 by kdvarako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_env(char *key, char *value, t_env **env)
{
	t_env	*new;

	new = ft_env_new(key, value);
	ft_env_add_back(env, new);
}

void	add_set_env(char *key, char *value, t_env **env)
{
	t_env	*new;

	if (find_key_env(key, env) == 0)
	{
		new = ft_env_new(key, value);
		ft_env_add_back(env, new);
	}
	else
	{
		set_value(key, value, env);
		free (key);
	}
}

void	save_env(char **envp, t_env **env, int *exit_status)
{
	int		i;
	int		j;
	int		len;
	char	*ptr;
	char	*key;

	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] != '=' && envp[i][j] != '\0')
			j++;
		key = ft_strndup(envp[i], j);
		j++;
		len = 0;
		ptr = &envp[i][j];
		while (envp[i][j] != '\0')
		{
			len++;
			j++;
		}
		add_env(key, ft_strndup(ptr, len), env);
		i++;
	}
	env[0]->exit_status = exit_status;
}

void	save_env_empty(t_env **env, int *exit_status)
{
	char	*value;
	char	cwd[256];

	add_env(ft_strdup("PWD"), ft_strdup(getcwd(cwd, sizeof(cwd))), env);
	add_env(ft_strdup("OLDPWD"), NULL, env);
	add_env(ft_strdup("SHLVL"), ft_strdup("1"), env);
	value = ft_strjoin(ft_strdup(getcwd(cwd, sizeof(cwd))), \
		ft_strdup("./minishell"));
	add_env(ft_strdup("_"), value, env);
	env[0]->exit_status = exit_status;
}

void	save_environment(char **envp, t_env **env, int *exit_status)
{
	if (*envp == NULL)
		save_env_empty(env, exit_status);
	else
	{
		save_env(envp, env, exit_status);
		set_value("_", ft_strdup("./minishell"), env);
	}
}
