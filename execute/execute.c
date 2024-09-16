/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 11:29:41 by kdvarako          #+#    #+#             */
/*   Updated: 2024/09/16 17:19:44 by kdvarako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <limits.h>

/*
function checks if there is a flag "-n" or "-nnn..." &
returns 0 if not or 1 if yes
*/
int	ft_if_newline(char *s)
{
	unsigned int	i;

	i = 1;
	if (s != NULL && s[0] == '-')
	{
		while (s[i] != '\0')
		{
			if (s[i] != 'n')
				break ;
			i++;
		}
		if (i == ft_strlen(s))
			return (1);
	}
	return (0);
}

void	exe_echo(t_parc *node)
{
	t_arg	*arg;
	int		fl_n;
	int		len;

	if (node->redirs_in == NULL && node->redirs_out == NULL)
	{
		arg = node->args;
		len = ft_size_arg(arg) - 1;
		fl_n = ft_if_newline(arg->value);
		if (fl_n == 1)
		{
			arg = arg->next;
			len--;
		}
		while (arg != NULL)
		{
			printf("%s", arg->value);
			if (len > 0)
				printf(" ");
			arg = arg->next;
			len--;
		}
		if (fl_n == 0)
			printf("\n");
	}
}

void	exe_cd(t_parc *node, t_env **env)
{
	char	*cur_pwd;
	char	buf[PATH_MAX];
	int		res;

	cur_pwd = get_value("PWD", env);
	if (node->args == NULL)
		res = chdir(get_value("HOME", env));
	else
		res = chdir(node->args->value);
	if (res == 0)
	{
		//printf("pwd buf: %s\n", getcwd(buf, sizeof(buf)));
		//printf("pwd before: %s\n", get_value("PWD", env));
		set_value("PWD", getcwd(buf, sizeof(buf)), env);  //allocate? what return getcwd - err?
		//printf("pwd after: %s\n", get_value("PWD", env));
		//printf("old after: %s\n", get_value("OLDPWD", env));
		set_value("OLDPWD", cur_pwd, env);
		//printf("old after: %s\n", get_value("OLDPWD", env));

	}
}

void	exe_pwd(t_parc *node, t_env **env)
{
	if (node->redirs_in == NULL && node->redirs_out == NULL)
		printf("%s\n", get_value("PWD", env));
}

void	exe_export(t_parc *node, t_env **env)
{
	if (node->args == NULL && node->redirs_in == NULL \
		&& node->redirs_out == NULL)
		ft_env_sort_declare(*env);
}

void	exe_unset(t_parc *node, t_env **env)
{
	/*if (node->args == NULL && node->redirs_in == NULL \
		&& node->redirs_out == NULL)
		*/
	if (node->redirs_in == NULL && node->redirs_out == NULL)
		ft_putstr_fd("unset\n", 1);
	if (env == NULL)
		printf("tmp msg\n");
}

void	exe_env(t_parc *node, t_env **env)
{
	if (node->redirs_in == NULL && node->redirs_out == NULL)
	{
		ft_env_print(env);
		set_value("_", ft_strdup("env"), env);
	}
}

int	if_builtin(char *cmd)
{
	/*
	function returns 0 if cmd is one of builtin
	*/
	if (ft_strcmp(cmd, "echo") == 0)
		return (0);
	if (ft_strcmp(cmd, "cd") == 0)
		return (0);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (0);
	if (ft_strcmp(cmd, "export") == 0)
		return (0);
	if (ft_strcmp(cmd, "unset") == 0)
		return (0);
	if (ft_strcmp(cmd, "env") == 0)
		return (0);
	//if (ft_strcmp(cmd, "exit") == 0)
		//return (0);
	return (1);
}

void	execute_builtin(t_parc *node, t_env **env)
{
	if (ft_strcmp(node->cmd, "echo") == 0)
		exe_echo(node);
	else if (ft_strcmp(node->cmd, "cd") == 0)
		exe_cd(node, env);
	else if (ft_strcmp(node->cmd, "pwd") == 0)
		exe_pwd(node, env);
	else if (ft_strcmp(node->cmd, "export") == 0)
		exe_export(node, env);
	else if (ft_strcmp(node->cmd, "unset") == 0)
		exe_unset(node, env);
	else if (ft_strcmp(node->cmd, "env") == 0)
		exe_env(node, env);
	//else if (ft_strcmp(node->cmd, "exit") == 0)
		//exe_exit(node, env);
}
