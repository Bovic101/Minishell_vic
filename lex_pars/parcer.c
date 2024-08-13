/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 18:33:46 by kdvarako          #+#    #+#             */
/*   Updated: 2024/08/11 15:37:41 by kdvarako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*save_cmd(t_token *node)
{
	int		i;
	char	*cmd;

	cmd = NULL;
	cmd = ft_strndup(node->ptr, node->len);
	i = 0;
	while (cmd[i] != '\0')
	{
		cmd[i] = ft_tolower(cmd[i]);
		i++;
	}
	return (cmd);
}

t_token	*save_redir(t_token *node, t_env **env, t_redirect **redirs)
{
	char	*rtype;
	char	*rfile;

	rtype = NULL;
	rfile = NULL;
	rtype = ft_strndup(node->ptr, node->len);
	node = node->next;
	while (node->type == SEPARATOR)
		node = node->next;
	if (node->type == WORD)
		rfile = ft_strndup(node->ptr, node->len);
	else if (node->type == EXPAND_VAR)
		rfile = expand(node->ptr, node->len, env, 6);
	add_redir(rtype, rfile, redirs);
	return (node);
}

t_token	*save_pipe(t_token *node, char *cmd, t_env **env, t_parc **parc)
{
	t_arg		*args;
	t_redirect	*redirs;

	redirs = NULL;
	args = NULL;
	while (node != NULL && node->type != PIPE)
	{
		if (node != NULL && node->type == WORD && cmd == NULL)
			cmd = save_cmd(node);
		else if (node != NULL && \
			(node->type == REDIR_IN || node->type == REDIR_IN2 \
			|| node->type == REDIR_OUT || node->type == REDIR_OUT2))
			node = save_redir(node, env, &redirs);
		else if (node != NULL && node->type == WORD)
			add_args(ft_strndup(node->ptr, node->len), &args);
		else if (node != NULL && (node->type == EXPAND_VAR \
			|| node->type == EXPAND_VAR_Q))
			add_args(expand(node->ptr, node->len, env, node->type), &args);
		else if (node != NULL && node->type == SEPARATOR && args != NULL)
			add_args(ft_strndup(" ", 1), &args);
		node = node->next;
	}
	ft_plst_add_back(parc, ft_plst_new(cmd, args, redirs));
	return (node);
	//free redirs, args ?
}

void	parcer(t_token **token, t_parc **parc, t_env **env)
{
	t_token		*node;
	char		*cmd;

	if (!token)
		return ;
	node = *token;
	while (node != NULL)
	{
		cmd = NULL;
		node = save_pipe(node, cmd, env, parc);
		if (node != NULL)
			node = node->next;
		//free cmd ?
	}
}
