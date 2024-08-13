/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 11:49:12 by kdvarako          #+#    #+#             */
/*   Updated: 2024/08/13 16:44:54 by kdvarako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_env(char *key, char *value, t_env **env)
{
	t_env	*new;

	new = ft_env_new(key, value);
	ft_env_add_back(env, new);
}

void	add_exitstatus(t_env **env)
{
	char	*key;
	char	*value;

	key = ft_strdup("_exit_code");
	value = ft_strdup("0");
	add_env(key, value, env);
}

void	save_env(char **envp, t_env **env)
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
	add_exitstatus(env);
}

void	save_env_empty(t_env **env)
{
	char	*key_oldpwd;
	char	*key_pwd;
	char	*value;
	char	cwd[256];

	key_pwd = ft_strdup("PWD");
	add_env(key_pwd, ft_strdup(getcwd(cwd, sizeof(cwd))), env);
	key_oldpwd = ft_strdup("OLDPWD");
	add_env(key_oldpwd, NULL, env);
	//add_env()
	add_exitstatus(env);
}

void	save_environment(char **envp, t_env **env)
{
	if (*envp == NULL)
		save_env_empty(env);
	else
		save_env(envp, env);
}
